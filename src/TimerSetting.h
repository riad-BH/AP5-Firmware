#ifndef H_TIMER1_SETTING
#define H_TIMER1_SETTING
#include <Arduino.h>

// Setting timer1 to give an interruption in micro-seconds for X Y axis motors
// pulses
inline void setTimer1(const uint16_t microTime)
{
  TCCR1A = 0;
  TIMSK1 = 2;
  OCR1A = microTime * 16;
  TCCR1B = _BV(WGM12) | _BV(CS10);
}

// Setting timer2 for the temperature control ISR
inline void setTimer2()
{
  TCCR2A = 0;
  TCCR2B = _BV(CS02) | _BV(CS01) | _BV(CS00);
  TIMSK2 = _BV(TOIE0);
}

// Setting timer3 to give an interruption in micro-seconds for Z E axismotors
// pulses
inline void setTimer3(const uint16_t microTime)
{
  TCCR3A = 0;
  TIMSK3 = 2;
  OCR3A = microTime * 16;
  TCCR3B = _BV(WGM32) | _BV(CS30);
}

// Setting timer4 for PWM signal for the mosfet (Temperature control) on PIN 6
inline void setTimer4()
{
  TCCR4A = _BV(WGM10) | _BV(WGM12);
  TCCR4A |= _BV(COM1A1);
  TCCR4B = _BV(CS11) | _BV(CS10);
  OCR4A = 125;
}

// Reset the timer counter and stop the timer
inline void stopTimer1()
{
  TCCR1B = 0;
  TCNT1 = 0;
}
#endif // H_TIMER1_SETTING
