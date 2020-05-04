#include "LimitSwitch.h"

/************************************************/

#define mq_tail mq.mouvements_array[mq.tail]

void LimitSwitchs::fLSFowardX(MouvementQueue &mq)
{
  if (mq.getDx_state(mq.tail))
  {
    if (mq.getDx(mq.tail) > mq.getDy(mq.tail))
    {
      mq_tail.step_xy = mq.getDx(mq.tail);
    }
    else
    {
      mq_tail.step_xy = mq.getDy(mq.tail);
    }
  }
}

void LimitSwitchs::fLSBackwardX(MouvementQueue &mq)
{
  /* if (_FLAG_dx_is_negative)
  {
    if (_dx > _dy)
    {
      step = _dx;
    }
    else
    {
      step = _dy;
    }
  }*/
}

void LimitSwitchs::fLSFowardY(MouvementQueue &mq)
{
  /* if (_FLAG_dy_is_negative)
  {
    if (_dy > _dx)
    {
      step = _dy;
    }
    else
    {
      step = _dx;
    }
  }*/
}

void LimitSwitchs::fLSBackwardY(MouvementQueue &mq)
{
  /* if (!_FLAG_dy_is_negative)
  {
    if (_dy > _dx)
    {
      step = _dy;
    }
    else
    {
      step = _dx;
    }
  }*/
}
