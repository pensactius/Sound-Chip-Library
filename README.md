Sound Chip Library
==================

This is a library for sending raw data to a variety of sound chips used in arcade/computer systems from the 80s. This is a very low level library so don't expect any high level functionality like playing notes or songs. You have the [Video Game Music Library](https://github.com/pensactius/Video-Game-Music-Library) for that (which uses this library for low data transfer to the sound chips)

Tested and developed on ESP32, an attempt is also made to provide ESP8266 compatibility. But due to the reduced number of usable pins in ESP8266 boards, it's not that useful. Thus ESP8266 support may be dropped. Support for AVR boards is planned for the near future.

## Sound Chips supported

The following sound chips are supported:

* SN76489

## Installation

The library can be installed from the PlatfromIO library manager or you can declare library dependencies in "platformio.ini" configuration file using lib_deps option.

```ini
# platformio.ini – project configuration file

[env:my_build_env]
platform = espressif8266
framework = arduino
lib_deps =
  # RECOMMENDED
  # Accept new functionality in a backwards compatible manner and patches
  pensactius/Sound Chip Library @ ^0.2.0
```

## Simple example

The library is very simple to use. The following is the example **TestChip** provided in the library:

```c++
include <Arduino.h>
#include <Sn76489.h>


//                     LSB                     MSB
//                     D7  D6  D5  D4  D3  D2  D1  D0 ~WE ~CE
#if defined ESP32
Sn76489 psg = Sn76489( 15,  2,  0,  4, 16, 17,  5, 18, 19, 21 );
#elif defined ESP8266
Sn76489 psg = Sn76489( D0, D1, D2, D3, D4, D5, D6, D7, D8 );
#endif


void setup() {
	Serial.begin(115200);

	// Initialize the sound chip. The sound chip is muted when begin() is called.
	psg.begin();

	// Show some internal debug info
	psg.dbgPrint();

	// Write some data to the chip
	psg.writeData(0x8b);	// A <-- C-4 low 4 bits
	psg.writeData(0x1a);	// A <-- C-4 high 6 bits
	psg.writeData(0x90);	// A volume <-- Max
	delay(2000);			// Listen it for 2s

	psg.writeData(0xAf);	// B <-- C-4 detuned a bit higher
	psg.writeData(0x1a);
	psg.writeData(0xB0);	// B volume <-- Max
	delay(2000);			// Listen both channels A and B

	psg.writeData(0xCC);	// C <-- C-3 low 4 bits
	psg.writeData(0x35);	// C <-- C-3 high 6 bits
	psg.writeData(0xD0);	// C volume <-- Max
	delay(2000);			// Listen A, B and C channels

	// Silence all channels when finished
	psg.muteAll();

}

void loop() {

}
```

Basically you define an object of the corresponding sound chip class and initialize it with the pins used to communicate to the chip. After initializing the sound chip by calling the ```.begin()``` method, you can send data by calling the ```.writeData()``` method.

