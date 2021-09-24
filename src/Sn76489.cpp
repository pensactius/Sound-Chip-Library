#include <Arduino.h>
#include "Sn76489.h"

Sn76489::Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we) :
	m_dataBus { d7, d6, d5, d4, d3, d2, d1, d0 }, 
	m_we { we },
	m_ce { -1 },
	m_rdy { -1 }
{
	
}
Sn76489::Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce) :
	m_dataBus { d7, d6, d5, d4, d3, d2, d1, d0 }, 
	m_we { we },
	m_ce { ce },
	m_rdy { -1 }
{
	
}
Sn76489::Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce, int rdy) :
	m_dataBus { d7, d6, d5, d4, d3, d2, d1, d0 }, 
	m_we { we },
	m_ce { ce },
	m_rdy { rdy }
{
	
}


Sn76489::~Sn76489()
{

}

void
Sn76489::begin()
{
	enableBus();
}

void
Sn76489::dbgPrint() const
{
	Serial.print("Sn76489 data(d7,d6,d5,d4,d3,d2,d1,d0), (we, ce): data(");
	for (auto data_pin: m_dataBus) {
		Serial.print(data_pin);
		Serial.print(",");
	}
	Serial.print("), (");
	Serial.print(m_we); Serial.print(", ");
	Serial.print(m_ce); Serial.println(")");
}

void Sn76489::writeData(uint8_t data) const
{
	// Send data through Data Bus
	//	 7  6  5  4 |  3  2  1  0
	//	 1  0  1  1 |  0  1  1  0
	//	D0 D1 D2 D3 | D4 D5 D6 D7
	for (int i=0; i<8; i++)
	{
		int bitValue = data & 1;
		int dataPin = m_dataBus[i];
		digitalWrite (dataPin, bitValue);
		data = data >> 1;
	}

	// CE / WE Active
	digitalWrite(m_we, LOW);
	digitalWrite(m_ce, LOW);
	delayMicroseconds(10);

	// CE / WE InActive
	digitalWrite(m_we, HIGH);
	digitalWrite(m_ce, HIGH);

}

void Sn76489::muteAll() const
{
	writeData(B10011111);
	writeData(B10111111);
	writeData(B11011111);
	writeData(B11111111);
}
/**********************************************************************+\
 * PRIVATE FUNCTIONS
\***********************************************************************/

void
Sn76489::enableBus() const
{
	// Data pins as OUTPUTs
	for (auto pin : m_dataBus)
		pinMode(pin, OUTPUT);

	pinMode(m_we, OUTPUT);
	
	// Set WE and CE Inactive
	digitalWrite(m_we, 1);
	digitalWrite(m_ce, 1);
}
