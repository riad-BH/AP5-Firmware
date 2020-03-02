#include "LimitSwitch.h"

/*************** Extern Variables ***************/
// If dx is negative the flag is set to one
extern volatile uint8_t _FLAG_dx_is_negative;
// If dy is negative the flag is set to one
extern volatile uint8_t _FLAG_dy_is_negative;
/************************************************/
extern volatile int32_t _dx;
extern volatile int32_t _dy;
/************************************************/
// Motor steps for bresenham
extern volatile uint16_t step;
/************************************************/
void fLSFowardX()
{
  if (!_FLAG_dx_is_negative)
  {
    if (_dx > _dy)
    {
      step = _dx;
    }
    else
    {
      step = _dy;
    }
  }
}
/************************************************/
void fLSBackwardX()
{
  if (_FLAG_dx_is_negative)
  {
    if (_dx > _dy)
    {
      step = _dx;
    }
    else
    {
      step = _dy;
    }
  }
}
/************************************************/
void fLSFowardY()
{
  if (_FLAG_dy_is_negative)
  {
    if (_dy > _dx)
    {
      step = _dy;
    }
    else
    {
      step = _dx;
    }
  }
}
/************************************************/
void fLSBackwardY()
{
  if (!_FLAG_dy_is_negative)
  {
    if (_dy > _dx)
    {
      step = _dy;
    }
    else
    {
      step = _dx;
    }
  }
}
/************************************************/
