/*!
 *  @file Ym2413.h
 *
 * This file is part of the Sound Chip Library, providing low level support
 * for Ym2413 sound chips. This chip is was widely used in arcade systems,
 * Sega machines and consumer computers in the 80s.
 *
 * Written by Andrés Mata (PensActius) 2024.
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

class Ym2413 : public ISoundChip
{

public:
	Ym2413(
		int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0,
		int cs, int we, int ao, int ic);
	~Ym2413();

	void initControlPins();

	// Initialize Ym2413 sound chip, mostly pin modes (IN/OUT)
	void begin();

	// Write byte of data to Ym2413 sound chip
	void writeData(uint8_t data) const;

	// Not used in the Ym2413 sound chip
	void writeData(uint8_t reg, uint8_t data) const;

	void muteAll() const;

	void dbgPrint() const;

private:
	int m_cs;
	int m_we;
	int m_ao;
	int m_ic;
};
