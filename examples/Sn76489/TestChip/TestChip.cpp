#include <Arduino.h>
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
