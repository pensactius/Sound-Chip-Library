#include "Sn76489.h"
#include <Arduino.h>
#include <unity.h>

Sn76489 psg = Sn76489(19, 18, 17, 16, 15, 14, 13, 12, 5, 4);

void setUp(void)
{
    psg.begin();
}

void tearDown(void)
{
    // clean stuff up here
}

void test_databus_pins(void)
{
    TEST_ASSERT_EQUAL(19, psg.m_dataBus[0]);
    TEST_ASSERT_EQUAL(18, psg.m_dataBus[1]);
    TEST_ASSERT_EQUAL(17, psg.m_dataBus[2]);
    TEST_ASSERT_EQUAL(16, psg.m_dataBus[3]);
    TEST_ASSERT_EQUAL(15, psg.m_dataBus[4]);
    TEST_ASSERT_EQUAL(14, psg.m_dataBus[5]);
    TEST_ASSERT_EQUAL(13, psg.m_dataBus[6]);
    TEST_ASSERT_EQUAL(12, psg.m_dataBus[7]);
}

void test_control_pins(void)
{
    TEST_ASSERT_EQUAL(5, psg.m_we);
    TEST_ASSERT_EQUAL(4, psg.m_ce);
    TEST_ASSERT_EQUAL(-1, psg.m_rdy);
}

void test_databus_high(void)
{
    psg.writeData(0xff);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(19));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(18));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(17));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(16));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(15));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(14));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(13));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(12));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(5));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(4));
}

void test_databus_low(void)
{
    psg.writeData(0);
    TEST_ASSERT_EQUAL(LOW, digitalRead(19));
    TEST_ASSERT_EQUAL(LOW, digitalRead(18));
    TEST_ASSERT_EQUAL(LOW, digitalRead(17));
    TEST_ASSERT_EQUAL(LOW, digitalRead(16));
    TEST_ASSERT_EQUAL(LOW, digitalRead(15));
    TEST_ASSERT_EQUAL(LOW, digitalRead(14));
    TEST_ASSERT_EQUAL(LOW, digitalRead(13));
    TEST_ASSERT_EQUAL(LOW, digitalRead(12));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(5));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(4));
}

void test_control_high(void)
{
    digitalWrite(psg.m_we, HIGH);
    digitalWrite(psg.m_ce, HIGH);
    delayMicroseconds(24);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(5));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(4));
}

void test_control_low(void)
{
    digitalWrite(psg.m_we, LOW);
    digitalWrite(psg.m_ce, LOW);
    delayMicroseconds(24);
    TEST_ASSERT_EQUAL(LOW, digitalRead(5));
    TEST_ASSERT_EQUAL(LOW, digitalRead(4));
}

void test_write_data(void)
{
    psg.writeData(0x8b); // A <-- C-4 low 4 bits (8b = 1000 1011)
    TEST_ASSERT_EQUAL(HIGH, digitalRead(19));
    TEST_ASSERT_EQUAL(LOW, digitalRead(18));
    TEST_ASSERT_EQUAL(LOW, digitalRead(17));
    TEST_ASSERT_EQUAL(LOW, digitalRead(16));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(15));
    TEST_ASSERT_EQUAL(LOW, digitalRead(14));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(13));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(12));
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_databus_pins);
    RUN_TEST(test_control_pins);
    RUN_TEST(test_write_data);
    //UNITY_END(); // stop unit testing
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop()
{
    
    if (i < max_blinks) {
        RUN_TEST(test_databus_high);
        RUN_TEST(test_control_high);
        delay(500);
        RUN_TEST(test_databus_low);
        RUN_TEST(test_control_low);
        delay(500);
        i++;
    } else if (i == max_blinks) {
        UNITY_END(); // stop unit testing
    }
}