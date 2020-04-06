#if !defined(H_TEMPCONTROL)
#define H_TEMPCONTROL

#include "ADC.h"
#include "Arduino.h"
#include "Pins.h"
#include "Sending.h"
#include "Setting.h"
#include "TimerSetting.h"



void setTempControl() ;

void setTemperature(uint16_t);

uint8_t readFlagADC();

void  timer2ISR();

void  setFlagADC() ;

void  resetFlagADC() ;

void regulateTemp();

#endif // H_TEMPCONTROL
