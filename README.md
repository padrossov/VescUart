# Fork lib from Peemouse (https://github.com/Peemouse/VescUart)           --> 512 bytes lower RAM usage

Edited to allow proper use of the ``setLocalProfile`` function.

CRC table stored in flash with the help of PROGMEM function. It saves 512 bytes of RAM!

Removed Debug messages.

Tested with the 5.01 VESC FW.


# VescUart

Arduino library for interfacing with a VESC over UART. This library is based upon the library written by RollingGecko (https://github.com/RollingGecko/VescUartControl). The library is updated for the newest VESC firmware (FW3.40) and cleaned up a bit. The library is not backwards compatible, so you have to upload the newest firmware to your VESC.

**Important:** This is not a dropin replacement for RollingGeckos library. You will have to make some changes to your software, as all functions and values is now within a class, see below.

## Implementation


crc table stored in flash:
```cpp
const PROGMEM unsigned short crc16_tab[] = { ... }


unsigned short crc16(unsigned char *buf, unsigned int len) {
	unsigned int i;
	unsigned short cksum = 0;
	for (i = 0; i < len; i++) {
		cksum = pgm_read_word (&crc16_tab[(((cksum >> 8) ^ *buf++) & 0xFF)]) ^ (cksum << 8);
	}
	return cksum;
}
```

To use the library you will have initiate the VescUart class and set the Serial port for UART communcation.

```cpp
#include <VescUart.h>

VescUart UART;

void setup() {
  Serial.begin(115200);

  while (!Serial) {;}

  UART.setSerialPort(&Serial);
}
```

You can now safely use the functions and change the values of the class. 

Getting VESC telemetry is easy:

```cpp
if ( UART.getVescValues() ) {
  Serial.println(UART.data.rpm);
  Serial.println(UART.data.inpVoltage);
  Serial.println(UART.data.ampHours);
  Serial.println(UART.data.tachometerAbs);
}
```
