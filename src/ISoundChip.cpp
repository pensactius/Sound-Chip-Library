/*!
 *  @file ISoundChip.cpp
 *
 * This file is part of the Sound Chip Library, providing low level support
 * for Sn76489 sound chips. This chip is was widely used in arcade systems,
 * Sega machines and consumer computers in the 80s.
 *
 * This file only provides a default constructor. All the interface methods
 * must be provided by the derived classes.
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
#include "ISoundChip.h"

ISoundChip::ISoundChip(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0)
    : m_dataBus{d7, d6, d5, d4, d3, d2, d1, d0}
{
}

ISoundChip::~ISoundChip()
{
}

void ISoundChip::initDataBus()
{
    // Data pins as OUTPUTs
    for (auto pin : m_dataBus)
    {
        pinMode(pin, OUTPUT);
    }
}

void ISoundChip::writeToDataBus(uint8_t data)
{
    // Send data through Data Bus
    //   7  6  5  4 |  3  2  1  0
    //   1  0  1  1 |  0  1  1  0
    //  D7 D6 D5 D4 | D3 D2 D1 D0
    for (int i = 0; i < 8; i++)
    {
        int bitValue = data & 1;
        int dataPin = m_dataBus[7-i];
        digitalWrite(dataPin, bitValue);
        data = data >> 1;
    }
}
