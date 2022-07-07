### Wistron-net IPMI OEM Commands (0x30)

* This series of commands are mainly used for diagnostic.

#### Read diag log Command: 0x80

* Read logs from BMC directory '/tmp/ipmi_log'.
* The maximun response 'N' is 1024.

`Request`

|Byte |Data
|---- |----
|NA   |NA

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).
|(2:N)|Response ascii code which reads from '/tmp/ipmi_log'.

#### Set Fan Speed Control Command: 0x21

* This Command is used to set fan control mode and fan PWM.

`Request`

|Byte |Data
|---- |----
|1    |**Control Mode**<br>1h = Manually Control<br>0h = Auto Control (follow fan control algorithm)
|2    |**Fan PWM Duty Cycle**<br>00h ~ 64h for 0% ~ 100% PWM duty cycle<br>This field is valid only if the request data byte #1 equals to 01h

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).

#### Get Fan Speed Control Command: 0x22

* This Command is used to get fan control mode and fan PWM.

`Request`

|Byte |Data
|---- |----
|NA   |NA

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).
|2    |**Control Mode**<br>1h = Manually Control<br>0h = Auto Control (follow fan control algorithm)
|3    |**Fan PWM Duty Cycle**<br>00h ~ 64h for 0% ~ 100% PWM duty cycle

#### I2C Read Write Command: 0x25

* Because standard IPMI Master Write-Read command only support 8 buses (ID 0 ~ 7).
* This OEM command is created to write-read all I2C buses of the BMC.

`Request`

|Byte |Data
|---- |----
|1    |Bus ID, 0-based (count from 0)
|2    |**Slave Address**<br>[7:1] Slave Address (7-bit)<br>[0] Reserved. Write as 0.
|3    |**Read Count**<br>Number of bytes to read, 1-based.<br>According to work as designed, the max read count is 255.<br>0 = no bytes to read.
|4    |**Offset**  Data Offset
|(5:N)|**Data to write**<br>Keep empty for this field if no data to write.<br>According to work as designed, the max write data length is 255 bytes.

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).
|(2:N)|Data read from specified salve address.

#### Set GPIO Command: 0x26

* This Command is used to set in/out direction and high/low level for a specific GPIO.
* GPIO number = port number * 8 + pin order of the port.

`Request`

|Byte |Data
|---- |----
|1    |GPIO Number
|2    |**GPIO Direction**<br>0 = Input<br>1 = Output
|3    |**GPIO Level**<br>0 = Low<br>1 = high<br>Note: If data byte 2 is 0, data byte 3 will be ignored

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).

#### Get GPIO Command: 0x27

* This Command is used to get in/out direction and high/low level for a specific GPIO.
* GPIO number = port number * 8 + pin order of the port.

`Request`

|Byte |Data
|---- |----
|1    |GPIO Number

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).
|2    |**GPIO Direction**<br>0 = Input<br>1 = Output
|3    |**GPIO Level**<br>0 = Low<br>1 = high

#### Get All GPIO Command: 0x28

* This Command is used to get direction and level of all GPIOs of BMC.

`Request`

|Byte |Data
|---- |----
|NA   |NA

`Response`

|Byte |Data
|---- |----
|1    |Completion code(0x00).
|2N   |Byte 2N: GPIO Direction of Port18E
|2N+1 |Byte 2N+1: GPIO Level of Port18E
