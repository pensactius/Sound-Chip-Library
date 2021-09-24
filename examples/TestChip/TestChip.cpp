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

	psg.begin();
	psg.muteAll();

	psg.dbgPrint();
}

void loop() {

}
