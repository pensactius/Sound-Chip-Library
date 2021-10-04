/*!
 *  @file ISoundChip.h
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

#pragma once
#include <stdint.h>

/*!
   @brief  Interface all sound chips must provide.
           This is a pure abstract class (aka interface) so all derived classes
           must provide the required interface methods.
 */
class ISoundChip
{

public:
    ~ISoundChip();

    // Initialize sound chip, pin modes (IN/OUT), etc.
    virtual void begin() = 0;
    // Write single byte of data to sound chip
    virtual void writeData(uint8_t data) const = 0;
    // Write byte of data to specified register/address in the sound chip
    virtual void writeData(uint8_t reg, uint8_t data) const = 0;

    // Silence all channels in the sound chip
    virtual void muteAll() const = 0;
};
