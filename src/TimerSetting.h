#ifndef H_TIMER1_SETTING
#define H_TIMER1_SETTING
#include <Arduino.h>
// Setting timer1 to give an interruption in micro-seconds for X Y axis motors pulses
void setTimer1(uint16_t);
// Setting timer2 for the temperature control ISR
void setTimer2();
// Setting timer3 to give an interruption in micro-seconds for Z E axismotors pulses
void setTimer3(uint16_t);
// Setting timer4 for PWM signal for the mosfet (Temperature control) on PIN 6
void setTimer4();
#endif // H_TIMER1_SETTING
