#ifndef H_EXTERNAL_INTERRUPTS
#define H_EXTERNAL_INTERRUPTS

#include <Arduino.h>
//  Setting INT0/1/2/3/4/5 for falling edge
void setInt(uint8_t);
//  Desactivating interrupt
void unsetInt(uint8_t);


#endif // H_EXTERNAL_INTERRUPTS