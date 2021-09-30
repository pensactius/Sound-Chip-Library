/*!
 *  @file Sn76489.h
 *
 * Video Game Music Library
 *
 * Written by Andrés Mata (PensActius) 2021.
 *
 * This filel is part of the Sound Chip Library.
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

#pragma once

#include "ISoundChip.h"


class Sn76489 : ISoundChip
{

public:
	Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we);
	Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce);
	Sn76489(int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0, int we, int ce, int rdy);
	~Sn76489();

	// Initialize Sn76489 sound chip, mostly pin modes (IN/OUT)
	void begin();
	
	// Write byte of data to Sn76489 sound chip
	void writeData(uint8_t data) const;
	
	// Not used in the Sn76489 sound chip
	void writeData(uint8_t reg, uint8_t data) const;
	
	void muteAll() const;

	void dbgPrint() const;

private:
	void enableBus() const;

	int m_dataBus[8];
	int m_we;
	int m_ce;
	int m_rdy;
};
