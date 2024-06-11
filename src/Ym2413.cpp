#include <Arduino.h>
#include "Ym2413.h"

/*!
    @brief    Instantiate a Ym2413 sound chip object.
    @param    d7-d0    Data pins (d7 is the most significant bit)
    @param    cs       Chip Select (active low)
    @param    we       Write Enable pin (active low)
    @param    ao       Data Bus control (active low)
    @param    ic       Reset pin (active low)
    @note     Call the object's begin() function before use -- pin
              initialization is performed there!
*/

Ym2413::Ym2413(
    int d7, int d6, int d5, int d4, int d3, int d2, int d1, int d0,
    int cs, int we, int ao, int ic) : 
    ISoundChip{d7, d6, d5, d4, d3, d2, d1, d0}, 
    m_cs{cs}, 
    m_we{we}, 
    m_ao{ao}, 
    m_ic{ic}
{
}

void Ym2413::initControlPins()
{
    pinMode(m_cs, OUTPUT);
    pinMode(m_we, OUTPUT);
    pinMode(m_ao, OUTPUT);
    pinMode(m_ic, OUTPUT);

    // Disable chip by default (needed?)
    digitalWrite(m_cs, 1);
}

void Ym2413::begin()
{
    ISoundChip::initDataBus();
    initControlPins();
}

// Not implemented in ym2413
void Ym2413::writeData(uint8_t data)
{
}

// Write data to a register
void Ym2413::writeData(uint8_t reg, uint8_t data)
{
    // From the datasheet
    // CS WE A0
    // 1  x  x  = Bus inactive
    // 0  0  0  = Select register address
    // 0  0  1  = Write register data

    // ------------------------------------------------------
    // Write register address
    // ------------------------------------------------------
    // rise edge, still nothing is sent to UC
    digitalWrite(m_cs, 1);
    digitalWrite(m_ao, 0);
    writeToDataBus(reg);
    // fall edge, data is sent to UC
    digitalWrite(m_cs, 0);
    // wait for 12 master clock cycles 
    // (at 3.5Mhz that is 4 microseconds, rounded up)
    delayMicroseconds(4);

    // ------------------------------------------------------
    // Write data
    // ------------------------------------------------------
    // rise edge, still nothing is sent to UC
    digitalWrite(m_cs, 1);
    digitalWrite(m_ao, 1);
    writeToDataBus(data);
    // fall edge, data is sent ot UC
    digitalWrite(m_cs, 0);
    // wait for 84 master clock cycles 
    // (at 3.5Mhz is 24 microseconds, rounded up)
    delayMicroseconds(24);

    // Disable UC
    digitalWrite(m_cs, 1);
}

void Ym2413::muteAll()
{
}

void Ym2413::dbgPrint() const
{
}
