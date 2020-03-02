#ifndef H_PROCESSING
#define H_PROCESSING

#include <Arduino.h>
#include "Setting.h"
#include "Pins.h"
#include "ConstDefines.h"

uint8_t fProcessing(char *, char[8], int32_t *, int32_t *, int32_t *);
void fSetLimits(float *, float *, float *);


#endif // H_PROCESSING
