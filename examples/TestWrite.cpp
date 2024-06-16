#include <Arduino.h>
#include "Ym2413.h"

Ym2413 ym2413{19, 18, 17, 16, 15, 14, 13, 12,
              5, 4, 2, 0};

void setup()
{
    Serial.begin(115200);
    ym2413.begin();

    ym2413.writeData(0x30, 0x78);
    ym2413.writeData(0x20, 0x12);
}

void loop()
{
}