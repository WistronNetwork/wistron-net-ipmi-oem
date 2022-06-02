### Wistron-net IPMI OEM Commands (0x34)

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

#### I2c Read Write Command: 0x81

* Read logs from BMC directory '/tmp/ipmi_log'.
* The maximun response 'N' is 1024.

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
