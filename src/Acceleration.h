#ifndef H_ACCELERATION
#define H_ACCELERATION

#include <Arduino.h>
#include "Setting.h"
#include "ConstDefines.h"

void fAccelCompute(int32_t* dX,int32_t* dY);
void fAccelCompute(int32_t* dX,int32_t* dY,int32_t* dZ);

#endif // END H_ACCELERATION
