#include "TimerSetting.h"

void setTimer1(uint16_t microTime)
{
  TCCR1A = 0;
  TIMSK1 = 2;
  OCR1A = microTime * 16;
  TCCR1B = _BV(WGM12) | _BV(CS10);
}

void setTimer3(uint16_t microTime)
{
  TCCR3A = 0;
  TIMSK3 = 2;
  OCR3A = microTime * 16;
  TCCR3B = _BV(WGM32) | _BV(CS30);
}