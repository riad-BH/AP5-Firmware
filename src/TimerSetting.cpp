#include "TimerSetting.h"

void setTimer1(uint16_t microTime)
{
  TCCR1A = 0;
  TIMSK1 = 2;
  OCR1A = microTime * 16;
  TCCR1B = _BV(WGM12) | _BV(CS10);
}

void setTimer2()
{
  TCCR2A = 0;
  TCCR2B = _BV(CS02) | _BV(CS01) | _BV(CS00);
  TIMSK2 = _BV(TOIE0);
}

void setTimer3(uint16_t microTime)
{
  TCCR3A = 0;
  TIMSK3 = 2;
  OCR3A = microTime * 16;
  TCCR3B = _BV(WGM32) | _BV(CS30);
}

void setTimer4()
{
  TCCR4A = _BV(WGM10) | _BV(WGM12);
  TCCR4A |= _BV(COM1A1);
  TCCR4B = _BV(CS11) | _BV(CS10);
  OCR4A = 125;
}