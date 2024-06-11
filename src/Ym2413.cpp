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
    m_dataBus{d7, d6, d5, d4, d3, d2, d1, d0}, 
    m_cs{cs}, 
    m_we{we}, 
    m_ao{ao}, 
    m_ic{ic}
{
}

void Ym2413::begin()
{
    ISoundChip::initDataBus();
    initControlPins();
}

void Ym2413::writeData(uint8_t data) const
{
}

void Ym2413::writeData(uint8_t reg, uint8_t data) const
{
}

void Ym2413::muteAll() const
{
}

void Ym2413::dbgPrint() const
{
}
