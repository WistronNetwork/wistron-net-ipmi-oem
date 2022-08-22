/*
// Copyright (c) 2022 Wistron Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#include <ipmid/api.hpp>
#include <sdbusplus/message/types.hpp>
#include <oemcommands.hpp>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <phosphor-logging/log.hpp>
#include <openbmc/obmc-i2c.h>
#include <gpiod.h>
#include <openbmc/libgpio.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fru.hpp>
#include <ipmid/utils.hpp>

using namespace phosphor::logging;

namespace ipmi
{
static void registerOEMFunctions() __attribute__((constructor));

int sensorMergeValue(int offset, std::list<uint8_t>& valueList, double* value)
    __attribute__((weak));

ipmi::RspType<std::vector<uint8_t>> ipmiOemReadDiagLog()
{
    std::vector<uint8_t> rsp;
    char b;
    int count=0, MAX_COUNT=1024;
    char log1[] = "/tmp/ipmi_log";
    char log2[] = "/tmp/ipmi_log_tmp";
    std::string line;
    std::ifstream f1(log1);

    if(!f1.good())
        return ipmi::responseSuccess();

    while(!f1.eof() && count < MAX_COUNT){
        count++;
        f1.read(&b, 1);
        rsp.push_back(b);
    }

    if(!f1.eof()){
        std::ofstream f2;
        f2.open(log2);
        while (getline(f1, line)) {
            f2 << line << "\n";
        }
        f2.close();
        remove(log1);
        std::filesystem::copy(log2, log1);
        remove(log2);
    } else {
        remove(log1);
    }

    f1.close();
    return ipmi::responseSuccess(rsp);
}

ipmi::RspType<std::vector<uint8_t>> ipmiOemI2cReadWrite(uint8_t bus, uint8_t addr,
                                                        uint8_t rd_cnt, std::vector<uint8_t> wdata)
{
    int dev;
    char i2c_bus[20];
    uint8_t *wbuf = &wdata[0];
    sprintf(i2c_bus, "/dev/i2c-%d", bus);

    dev = open(i2c_bus, O_RDWR);
    if(dev < 0) {
        std::fprintf(stderr, "%s: open() failed\n", __func__);
        return ipmi::responseUnspecifiedError();
    }

    uint8_t *rbuf = (uint8_t *) malloc(rd_cnt * sizeof(uint8_t));
    i2c_rdwr_msg_transfer(dev, addr << 1, wbuf, wdata.size(), rbuf, rd_cnt);
    std::vector<uint8_t> rdata(rbuf, rbuf + rd_cnt);

    close(dev);
    free(rbuf);
    return ipmi::responseSuccess(rdata);
}

ipmi::RspType<> ipmiOemSetGPIO(uint8_t num, uint8_t direction, uint8_t level)
{
    gpio_desc_t *gdesc = NULL;
    gpio_direction_t dir;
    gpio_value_t value;

    // open gpio
    gdesc = gpio_open_by_offset("aspeed-gpio", num);
    if (gdesc == NULL) {
		return ipmi::responseUnspecifiedError();
    }

    // check whether direction is available
    dir = gpio_direction_str_to_type(direction ? "out" : "in");
	if (dir == GPIO_DIRECTION_INVALID) {
		phosphor::logging::log<level::ERR>("invalid direction:",
			                               entry("offset: %d", num));
		gpio_close(gdesc);
	    return ipmi::responseUnspecifiedError();
	}

    // set direction
    if (gpio_set_direction(gdesc, dir) != 0) {
		phosphor::logging::log<level::ERR>("failed to set gpio direction:",
			                               entry("offset: %d", num));
		gpio_close(gdesc);
	    return ipmi::responseUnspecifiedError();
	}

    // set value
	value = (level ? GPIO_VALUE_HIGH : GPIO_VALUE_LOW);
	if (gpio_set_value(gdesc, value) != 0) {
		phosphor::logging::log<level::ERR>("failed to set gpio value:",
			                                entry("offset: %d", num));
		gpio_close(gdesc);
	    return ipmi::responseUnspecifiedError();
	}

    gpio_close(gdesc);
    return ipmi::responseSuccess();
}

ipmi::RspType<uint8_t, uint8_t> ipmiOemGetGPIO(uint8_t num)
{
    gpio_desc_t *gdesc = NULL;
    gpio_direction_t dir;
    gpio_value_t value;
    uint8_t direction;

    // open gpio
    gdesc = gpio_open_by_offset("aspeed-gpio", num);
    if (gdesc == NULL)
		return ipmi::responseUnspecifiedError();

    if (gpio_get_direction(gdesc, &dir) != 0) {
		phosphor::logging::log<level::ERR>("failed to get gpio direction",
                                            entry("offset: %d", num));
		gpio_close(gdesc);
	    return ipmi::responseUnspecifiedError();
	}

    // get direction
    direction = (strcmp(gpio_direction_type_to_str(dir), "out") == 0)
                ? 1 : 0;

    //get value
    if (gpio_get_value(gdesc, &value) != 0) {
		phosphor::logging::log<level::ERR>("failed to get gpio value:",
                                            entry("offset: %d", num));
		gpio_close(gdesc);
	    return ipmi::responseUnspecifiedError();
	}

    gpio_close(gdesc);
    return ipmi::responseSuccess(direction, (uint8_t)value);
}

static void readallgpio(struct gpiod_chip *chip,
                               std::vector<uint8_t>& result)
{
    struct gpiod_line_iter *iter;
    unsigned int offset;
    struct gpiod_line *line;
    const char *consumer;
    int direction;
    uint8_t direction_val = 0, level_val = 0;
    gpio_desc_t *gdesc = NULL;
    gpio_value_t value;
    char shadow[10];

    iter = gpiod_line_iter_new(chip);
    if (!iter)
		phosphor::logging::log<level::ERR>("error creating line iterator");

    // read each gpio port
    gpiod_foreach_line(iter, line) {
        offset = gpiod_line_offset(line);
        consumer = gpiod_line_consumer(line);
        direction = gpiod_line_direction(line);

        // export gpio if it is not occupied by another process.
        snprintf(shadow, 10, "GPIO%d", offset);
        if (!gpiod_line_is_used(line) && direction == 1) {
            gpio_export_by_offset("aspeed-gpio", offset, shadow);
        }

        // gpio is readable in these two situation
        if ((!gpiod_line_is_used(line) && direction == 1) ||
             (consumer && strcmp("sysfs", consumer) == 0)) {
            // open gpio
            gdesc = gpio_open_by_offset("aspeed-gpio", offset);
            if (gdesc == NULL) {
                phosphor::logging::log<level::ERR>("failed to open gpio:",
                                                    entry("offset: %d", offset));
                return;
            }

            //get value
            if (gpio_get_value(gdesc, &value) != 0) {
                phosphor::logging::log<level::ERR>("failed to get gpio value:",
                                                    entry("offset: %d", offset));
                gpio_close(gdesc);
                return;
            }
            gpio_close(gdesc);

            // set gpio direction and value as one bit into 'result' variable.
            if (offset%8 == 0 && offset/8 >= 1) {
                direction_val |= (direction == 1) ? 0 : 1 << (offset % 8);
                level_val |= (uint8_t)value << (offset % 8);
                result.push_back(direction_val);
                result.push_back(level_val);
                direction_val = 0;
                level_val = 0;
            } else {
                direction_val |= (direction == 1) ? 0 : 1 << (offset % 8);
                level_val |= (uint8_t)value << (offset % 8);
            }
        }

        // unexport gpio
        if (!gpiod_line_is_used(line) && direction == 1)
            gpio_unexport(shadow);
    }

    // record the remain data in the tail of gpio list
    if (!(offset%8 == 0 && offset/8 >= 1)) {
        result.push_back(direction_val);
        result.push_back(level_val);
    }

    gpiod_line_iter_free(iter);
}

ipmi::RspType<std::vector<uint8_t>> ipmiOemGetAllGPIO()
{
    struct gpiod_chip_iter *chip_iter;
    struct gpiod_chip *chip;
    std::vector<uint8_t> result;

    chip_iter = gpiod_chip_iter_new();
    if (!chip_iter)
		phosphor::logging::log<level::ERR>("error accessing GPIO chips");

    gpiod_foreach_chip(chip_iter, chip)
        readallgpio(chip, result);

    return ipmi::responseSuccess(result);
}

/** @brief implements the set fan speed control command
 *  @param mode - Control Mode; 1h = Manually Control, 0h = Auto Control
 *  @param duty - Fan PWM Duty Cycle; 00h ~ 64h for 0% ~ 100% PWM duty cycle.
 *                This field is valid only if the mode equals to 01h
 *
 *  @returns IPMI completion code
 */
ipmi::RspType<> ipmiOemSetFanSpeedControl(uint8_t mode, uint8_t duty)
{
    const int MAX_COMMAND = 64;
    char command[MAX_COMMAND];

    // TODO: Mode control - currently only force mode (Manually Control)

    if (mode == 1) {
        snprintf(command, MAX_COMMAND,
                 "/usr/local/bin/fan-util --set %d ", duty);

        auto ret = system(command);
        if (ret) {
            return ipmi::responseUnspecifiedError();
        }
    }

    return ipmi::responseSuccess();
}

/** @brief implements the set fan speed control command
 *
 *  @returns IPMI completion code plus response data
 *   - mode - Control Mode; 1h = Manually Control, 0h = Auto Control
 *   - duty - Fan PWM Duty Cycle; 00h ~ 64h for 0% ~ 100% PWM duty cycle.
 */
ipmi::RspType<uint8_t, uint8_t> ipmiOemGetFanSpeedControl()
{
    const int MAX_BUFFER = 256;
    char buffer[MAX_BUFFER];
    uint8_t duty = 0;
    uint8_t mode = 0;
    std::string value;
    std::vector<std::string> result;
    FILE * stream;

    // TODO: Mode control - currently only force mode (Manually Control)
    mode = 1;

    stream = popen("/usr/local/bin/fan-util --get", "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, MAX_BUFFER, stream) != NULL) {
                value.append(buffer);
            }
        }

        auto ret = pclose(stream);
        if (ret) {
            return ipmi::responseUnspecifiedError();
        }

        /* fan-util output format should like below:
           Example - "Fan 1 RPM: 12344 PWM: 100 %".
           PWM value will be index 5 after do string split.
           If the format is different, it might got error */
        boost::split(result, value, boost::is_any_of(" "));
        duty = boost::numeric_cast<uint8_t>(boost::lexical_cast<int>(result[5]));
    } else {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::responseSuccess(mode, duty);
}

ipmi::RspType<> ipmiOemSetFruMfgDate(uint8_t fru, uint8_t lsbdate,
                                     uint8_t middate, uint8_t msbdate)
{
    FILE *fp;
    uint8_t buffer[3] = {};
    size_t numread, numwritten;
    uint8_t date_offset;

    if (FRU_MAX <= 0)
        return responseOutOfSpace();
    fp = fopen(frulist[fru],"rb+");
    if (NULL == fp) {
        return ipmi::responseUnspecifiedError();
    } else {
        fseek (fp , 3, SEEK_SET);
        memset(buffer, 0, 1);
        numread = fread(buffer, 1, 1, fp);

        if (numread == 0) {
            fclose(fp);
            return ipmi::responseUnspecifiedError();
        }
        date_offset = buffer[0] * 8 + 3;

        fseek (fp , date_offset, SEEK_SET);
        buffer[0] = lsbdate;
        buffer[1] = middate;
        buffer[2] = msbdate;

        numwritten = fwrite(buffer, 1, 3, fp);
        if (numwritten == 0) {
            fclose(fp);
            return ipmi::responseUnspecifiedError();
        }
    }
    fclose(fp);

    return ipmi::responseSuccess();
}

/** @brief implements the set I2C mux master select command
 *  @param select - 0: BMC, 1: CPU
 *
 *  @returns IPMI completion code
 */
ipmi::RspType<> ipmiOemSetI2cMuxMaster(uint8_t select)
{
    const int MAX_COMMAND = 64;
    char command[MAX_COMMAND];

    if (select == 0) {
        snprintf(command, MAX_COMMAND, "/usr/local/bin/mux-util --set i2c bmc");
    } else if (select == 1) {
        snprintf(command, MAX_COMMAND, "/usr/local/bin/mux-util --set i2c cpu");
    } else {
        return ipmi::responseCommandNotAvailable();
    }

    auto ret = system(command);
    if (ret) {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::responseSuccess();
}

/** @brief implements the get I2C mux master select command
 *
 *  @returns IPMI completion code plus response data
 *   - select - 0: BMC, 1: CPU
 */
ipmi::RspType<uint8_t> ipmiOemGetI2cMuxMaster()
{
    const int MAX_BUFFER = 32;
    char buffer[MAX_BUFFER];
    uint8_t select = 0;
    std::string value;
    std::vector<std::string> result;
    FILE * stream;

    stream = popen("/usr/local/bin/mux-util --get i2c", "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, MAX_BUFFER, stream) != NULL) {
                value.append(buffer);
            }
        }

        auto ret = pclose(stream);
        if (ret) {
            return ipmi::responseUnspecifiedError();
        }

        // mux-util output format is "BMC" or "CPU"
        if (value.compare(0, 3, "BMC") == 0) {
            select = 0;
        } else if (value.compare(0, 3, "CPU") == 0) {
            select = 1;
        } else {
            return ipmi::responseUnspecifiedError();
        }
    } else {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::responseSuccess(select);
}

/** @brief implements the set UART mux master select command
 *  @param select - 0: BMC, 1: CPU
 *
 *  @returns IPMI completion code
 */
ipmi::RspType<> ipmiOemSetUartMuxMaster(uint8_t select)
{
    const int MAX_COMMAND = 64;
    char command[MAX_COMMAND];

    if (select == 0) {
        snprintf(command, MAX_COMMAND, "/usr/local/bin/mux-util --set uart bmc");
    } else if (select == 1) {
        snprintf(command, MAX_COMMAND, "/usr/local/bin/mux-util --set uart cpu");
    } else {
        return ipmi::responseCommandNotAvailable();
    }

    auto ret = system(command);
    if (ret) {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::responseSuccess();
}

/** @brief implements the get UART mux master select command
 *
 *  @returns IPMI completion code plus response data
 *   - select - 0: BMC, 1: CPU
 */
ipmi::RspType<uint8_t> ipmiOemGetUartMuxMaster()
{
    const int MAX_BUFFER = 32;
    char buffer[MAX_BUFFER];
    uint8_t select = 0;
    std::string value;
    std::vector<std::string> result;
    FILE * stream;

    stream = popen("/usr/local/bin/mux-util --get uart", "r");
    if (stream) {
        while (!feof(stream)) {
            if (fgets(buffer, MAX_BUFFER, stream) != NULL) {
                value.append(buffer);
            }
        }

        auto ret = pclose(stream);
        if (ret) {
            return ipmi::responseUnspecifiedError();
        }

        // mux-util output format is "BMC" or "CPU"
        if (value.compare(0, 3, "BMC") == 0) {
            select = 0;
        } else if (value.compare(0, 3, "CPU") == 0) {
            select = 1;
        } else {
            return ipmi::responseUnspecifiedError();
        }
    } else {
        return ipmi::responseUnspecifiedError();
    }

    return ipmi::responseSuccess(select);
}

std::vector<std::string> getPathList(sdbusplus::bus::bus& bus, uint8_t channel)
{
    std::vector<std::string> path_list;
    auto ifname = getChannelName(channel);
    if (ifname.empty())
    {
        return {};
    }

    auto req = bus.new_method_call(MAPPER_BUS_NAME, MAPPER_OBJ, MAPPER_INTF,
                                   "GetSubTree");
    req.append(PATH_ROOT, 0, std::vector<std::string>{INTF_SENSORVAL});
    auto reply = bus.call(req);
    ObjectTree objs;
    reply.read(objs);

    for (const auto& [path, impls] : objs)
    {
        path_list.push_back(path);
    }

    return path_list;
}

int sensorMergeValue(int offset, std::list<uint8_t>& valueList, double *value)
{
    /* One dbus property only matches one parameter, so the size is always 1.
     * If there is a property that needs to be combined by more than one byte,
       we need to re-define the function in platform layer.
     */
    if (sensorparams[offset].size != 1) {
        return SENSOR_CONFIG_ERROR;
    }

    *value = (double)(valueList.front());
    valueList.pop_front();

    return SENSOR_SUCCESS;
}

static int findSensorPath(int i, std::list<uint8_t>& valueList)
{
    double value;
    int ret;
    std::vector<std::string> path_list;
    int size_count = 0;

    for (struct SensorParams sensorinfo : sensorparams) {
        size_count += sensorinfo.size;
    }

    if (size_count != valueList.size()) {
        phosphor::logging::log<level::INFO>(
                  "Input parameter length is not equal to configuration.");
        return SENSOR_OUT_OF_RANGE;
    }

    sdbusplus::bus::bus bus(ipmid_get_sd_bus_connection());
    path_list = getPathList(bus, CHANNEL_NUM);

    ret = sensorMergeValue(i, valueList, &value);

    if (ret)
        return SENSOR_CONFIG_ERROR;

    for (std::string path : path_list) {
        if (sensorparams[i].path == path) {
            setDbusProperty(bus,
                            PATH_SERVICE,
                            path.c_str(),
                            INTF_SENSORVAL,
                            "Value",
                            value);
        } else {
            return SENSOR_SET_PROPERTY_ERROR;
        }
    }
    return SENSOR_SUCCESS;
}

ipmi::RspType<uint8_t> ipmiOemSetExternalSensors(std::vector<uint8_t> valueVec)
{
    int size = sizeof(sensorparams) / sizeof(sensorparams[0]);

    std::list<uint8_t> valueList(valueVec.begin(), valueVec.end());
    for (int i=0;i<size;i++) {
        int ret = findSensorPath(i, valueList);
        if (ret) {
            switch (ret) {
                case SENSOR_OUT_OF_RANGE:
                    phosphor::logging::log<level::INFO>(
                        "Input parameter length is not equal to configuration.");
                    return ipmi::responseParmOutOfRange();
                case SENSOR_CONFIG_ERROR:
                    phosphor::logging::log<level::INFO>(
                        "Configuration setting error.");
                    return ipmi::responseUnspecifiedError();
                case SENSOR_SET_PROPERTY_ERROR:
                    phosphor::logging::log<level::INFO>(
                        "Cannot set dbus property suscessfully.");
                    return ipmi::responseSensorInvalid();
            }
        }
    }

    return ipmi::responseSuccess();
}

void registerOEMFunctions()
{
    phosphor::logging::log<level::INFO>(
        "Registering OEM commands");
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemTwo, WIS_CMD_READ_DIAG_LOG,
            ipmi::Privilege::User, ipmiOemReadDiagLog);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_I2C_READ_WRITE,
            ipmi::Privilege::User, ipmiOemI2cReadWrite);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_SET_GPIO,
            ipmi::Privilege::User, ipmiOemSetGPIO);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_GET_GPIO,
            ipmi::Privilege::User, ipmiOemGetGPIO);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_GET_ALL_GPIO,
            ipmi::Privilege::User, ipmiOemGetAllGPIO);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_SET_FAN_SPEED_CONTROL,
            ipmi::Privilege::User, ipmiOemSetFanSpeedControl);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_GET_FAN_SPEED_CONTROL,
            ipmi::Privilege::User, ipmiOemGetFanSpeedControl);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_SET_FRU_MFG_DATE,
            ipmi::Privilege::User, ipmiOemSetFruMfgDate);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_SET_I2C_MUX_MASTER,
            ipmi::Privilege::User, ipmiOemSetI2cMuxMaster);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_GET_I2C_MUX_MASTER,
            ipmi::Privilege::User, ipmiOemGetI2cMuxMaster);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_SET_UART_MUX_MASTER,
            ipmi::Privilege::User, ipmiOemSetUartMuxMaster);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_GET_UART_MUX_MASTER,
            ipmi::Privilege::User, ipmiOemGetUartMuxMaster);
    ipmi::registerHandler(ipmi::prioOemBase, ipmi::netFnOemOne, WIS_CMD_SET_INTERNAL_SENSOR_READING,
            ipmi::Privilege::User, ipmiOemSetExternalSensors);
}
}