/*!
 *  @file Sn76489.cpp
 *
 * This file is part of the Sound Chip Library, providing low level support
 * for Sn76489 sound chips. This chip is was widely used in arcade systems,
 * Sega machines and consumer computers in the 80s.
 *
 * Written by Andrés Mata (PensActius) 2021.
 *
 * MIT license, all text above must be included in any redistribution
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <Arduino.h>
#include "Sn76489.h"

// CONSTRUCTORS, DESTRUCTOR -------------------------------------------

/*!
    @brief    Instantiate a Sn76489 sound chip object. Only a single
              control pin (~WE) is connected. ~CE is usually connected 
              to GND or to ~WE.
    @param    d7-d0    Data pins (d0 is the most significant bit)
    @param    we       Write Enable pin (active low)
    @note     Call the object's begin() function before use -- pin
              initialization is performed there!
*/
Sn76489::Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we) :
  m_dataBus { d7, d6, d5, d4, d3, d2, d1, d0 }, 
  m_we { we },
  m_ce { -1 },
  m_rdy { -1 }
{
  
}

/*!
    @brief    Instantiate a Sn76489 sound chip object. Both ~WE and ~WE
              are used to control data transfer.
    @param    d7-d0    Data pins (d0 is the most significant bit)
    @param    we       Write Enable pin (active low)
    @param    ce       Chip Enable pin (active low)
    @note     Call the object's begin() function before use -- pin
              initialization is performed there!
*/
Sn76489::Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce) :
  m_dataBus { d7, d6, d5, d4, d3, d2, d1, d0 }, 
  m_we { we },
  m_ce { ce },
  m_rdy { -1 }
{
  
}

/*!
    @brief    Instantiate a Sn76489 sound chip object. Both ~WE and ~WE
              are used to control data transfer, and Ready pin is used 
              to acknowledge the end of a data transfer.
    @param    d7-d0    Data pins (d0 is the most significant bit)
    @param    we       Write Enable pin (active low)
    @param    ce       Chip Enable pin (active low)
    @param    rdy      Ready pin (active high)
    @note     Call the object's begin() function before use -- pin
              initialization is performed there!
*/

Sn76489::Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce, int rdy) :
  m_dataBus { d7, d6, d5, d4, d3, d2, d1, d0 }, 
  m_we { we },
  m_ce { ce },
  m_rdy { rdy }
{
  
}

/*!
    @brief    Just a default contructor. Nothing else is needed.
*/
Sn76489::~Sn76489()
{

}

/*!
    @brief    Configure microcontroller pins for sound chip interfacing.
              It also mutes the sound chip.
*/
void
Sn76489::begin()
{
  enableBus();
  muteAll();
}

/*!
    @brief    Send a single byte of data to the sound chip.
    @param    data    Data byte to send         
*/
void Sn76489::writeData(uint8_t data) const
{
  // Send data through Data Bus
  //   7  6  5  4 |  3  2  1  0
  //   1  0  1  1 |  0  1  1  0
  //  D0 D1 D2 D3 | D4 D5 D6 D7
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

void Sn76489::writeData(uint8_t reg, uint8_t data) const
{

}

void Sn76489::muteAll() const
{
  writeData(B10011111);
  writeData(B10111111);
  writeData(B11011111);
  writeData(B11111111);
}

void
Sn76489::dbgPrint() const
{
  Serial.print("\n[Sn76489]\t data pins {");
  for (auto data_pin: m_dataBus) {
    Serial.print(data_pin);
    Serial.print(",");
  }
  Serial.print("} ~WE: "); Serial.print(m_we);
  Serial.print(" ~CE: "); Serial.print(m_ce); 
  
  Serial.println();
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
