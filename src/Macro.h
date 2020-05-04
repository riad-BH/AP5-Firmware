#ifndef __MACRO_H__
#define __MACRO_H__
#include "Arduino.h"

#define ENTER_LV1_CRITICAL_SECTION cli()
#define EXIT_LV1_CRITICAL_SECTION sei()

#define ENTER_LV2_CRITICAL_SECTION cli();const uint8_t _sreg = 
#define EXIT_LV2_CRITICAL_SECTION SREG  = _sreg;sei()
#endif // __MACRO_H__