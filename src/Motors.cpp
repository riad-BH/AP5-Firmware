#include "Motors.h"
#include "IOFunctions.h"

#define mq_tail mq.mouvements_array[mq.tail]

void inline Motors::fMoveExtruder(MouvementQueue &mq)
{

  if (mq_tail.step_e < mq.getExtruderSpeed(mq.tail))
  {
    mq_tail.step_e++;
  }
  else
  {
    PORTL |= (_BV(PIN_E_STEP));
    mq_tail.step_e = 0;
  }
}

void inline Motors::fStopExtruder(MouvementQueue &mq)
{
  PORTL &= ~(_BV(PIN_E_STEP));
}

/*******************************************************/
void inline Motors::accelerateXY(MouvementQueue &mq)
{
  if (mq_tail.step_xy < mq.getAccelerationDistance(mq.tail))
  {
    mq.setImp_size(mq.getImp_size(mq.tail) - mq.getAcceleration_x16(mq.tail),
                   mq.tail);
    OCR1A = mq.getImp_size(mq.tail);
  }

  else if (mq_tail.step_xy < mq.getDecelerationDistance(mq.tail) &&
           mq.getAccelerationDistance(mq.tail) < mq_tail.step_xy)
  {
    mq.setImp_size(mq.getImp_value_x16(mq.tail), mq.tail);
    OCR1A = mq.getImp_size(mq.tail);
  }
  else if (mq.getDecelerationDistance(mq.tail) <= mq_tail.step_xy)
  {
    mq.setImp_size(mq.getImp_size(mq.tail) + mq.getAcceleration_x16(mq.tail),
                   mq.tail);
    OCR1A = mq.getImp_size(mq.tail);
  }
}
/*******************************************************/

/*******************************************************/
void inline Motors::accelerateZ(MouvementQueue &mq)
{
  if (mq_tail.step_z < mq.getAccelerationDistanceZ(mq.tail))
  {
    mq.setImp_size_z(
        mq.getImp_size_z(mq.tail) - mq.getAcceleration_z_x16(mq.tail), mq.tail);
    OCR1A = mq.getImp_size_z(mq.tail);
  }

  else if (mq_tail.step_z < mq.getDecelerationDistanceZ(mq.tail) &&
           mq.getAccelerationDistanceZ(mq.tail) < mq_tail.step_z)
  {
    mq.setImp_size_z(mq.getImp_value_z_x16(mq.tail), mq.tail);
    OCR1A = mq.getImp_size_z(mq.tail);
  }

  else if (mq.getDecelerationDistanceZ(mq.tail) < mq_tail.step_z)
  {
    mq.setImp_size_z(
        mq.getImp_size_z(mq.tail) + mq.getAcceleration_z_x16(mq.tail), mq.tail);
    OCR1A = mq.getImp_size_z(mq.tail);
  }
}
/*******************************************************/

/*******************************************************/ /*******************************************************/
/*******************************************************/ /*******************************************************/
/*******************************************************/ /*******************************************************/
/*******************************************************/ /*******************************************************/
/*******************************************************/ /*******************************************************/
/*******************************************************/ /*******************************************************/

void Motors::mouvementSorter(MouvementQueue &mq)
{

  switch (mq_tail.mouvement_state_selection)
  {
  case ms_null:
    mq.removeAvailable_mouvement();
    mq.incrementTail();
    if (mq.getAvailable_mouvement())
    {
      mouvementSorter(mq);
    }
    if (Flags::getFlag_machine() == 2)
    {
      Flags::setFlag_machine(RECEIVING);
    }
    break;

  case ms_x:
    setUpX(mq);
    setTimer1(mq.getImp_start(mq.tail));
    Flags::setFlag_motor_activated(1);
    break;

  case ms_y:
    setUpY(mq);
    setTimer1(mq.getImp_start(mq.tail));
    Flags::setFlag_motor_activated(1);
    break;

  case ms_xy:
    setUpX(mq);
    setUpY(mq);
    setTimer1(mq.getImp_start(mq.tail));
    Flags::setFlag_motor_activated(1);
    break;

  case ms_e:
    setUpE(mq);
    break;

  case ms_xe:
    setUpX(mq);
    setTimer1(mq.getImp_start(mq.tail));
    Flags::setFlag_motor_activated(1);
    break;

  case ms_ye:
    setUpY(mq);
    setTimer1(mq.getImp_start(mq.tail));
    Flags::setFlag_motor_activated(1);
    break;

  case ms_xye:
    setUpX(mq);
    setUpY(mq);
    setTimer1(mq.getImp_start(mq.tail));
    Flags::setFlag_motor_activated(1);
    break;

  case ms_z:
    setUpZ(mq);
    break;

  case ms_xz:
    setUpZ(mq);
    setUpX(mq);
    break;

  case ms_yz:
    setUpZ(mq);
    setUpY(mq);
    break;

  case ms_xyz:
    setUpZ(mq);
    setUpX(mq);
    setUpY(mq);
    Flags::setFlag_motor_activated(1);
    break;

  case ms_ze:
    setUpZ(mq);
    break;

  case ms_xez:
    setUpZ(mq);
    setUpX(mq);
    break;

  case ms_yez:
    setUpZ(mq);
    setUpY(mq);
    break;

  case ms_xyez:
    setUpZ(mq);
    setUpX(mq);
    setUpY(mq);
    break;

  default:
    break;
  }
}

void Motors::moveSteppers(MouvementQueue &mq)
{
  switch (mq_tail.mouvement_state_selection)
  {
  case ms_null:
    stopTimer1();
    break;

  case ms_x:
    moveX(mq);
    break;

  case ms_y:
    moveY(mq);
    break;

  case ms_xy:
    moveXY(mq);
    break;

  case ms_e:
    moveE(mq);
    break;

  case ms_xe:
    moveXE(mq);
    break;

  case ms_ye:
    moveYE(mq);
    break;

  case ms_xye:
    moveXYE(mq);
    break;

  case ms_z:
    moveZ(mq);
    break;

  case ms_xz:
    if (Flags::getFlag_motor_z_activated())
    {
      moveZ(mq);
    }
    else
    {
      moveX(mq);
    }
    break;

  case ms_yz:
    if (Flags::getFlag_motor_z_activated())
    {
      moveZ(mq);
    }
    else
    {
      moveY(mq);
    }
    break;

  case ms_xyz:
    if (Flags::getFlag_motor_z_activated())
    {
      moveZ(mq);
    }
    else
    {
      moveXY(mq);
    }
    break;

  case ms_ze:
    moveZ(mq);
    break;

  case ms_xez:
    if (Flags::getFlag_motor_z_activated())
    {
      moveZ(mq);
    }
    else
    {
      moveXE(mq);
    }
    break;

  case ms_yez:
    if (Flags::getFlag_motor_z_activated())
    {
      moveZ(mq);
    }
    else
    {
      moveYE(mq);
    }
    break;

  case ms_xyez:
    if (Flags::getFlag_motor_z_activated())
    {
      moveZ(mq);
    }
    else
    {
      moveXYE(mq);
    }
    break;

  default:
    break;
  }
}

void inline Motors::setUpX(MouvementQueue &mq)
{
  if (mq.getDx_state(mq.tail) == 2)
  {
    PORTB |= _BV(PIN_X_DIR);
  }
  else
  {
    PORTB &= ~_BV(PIN_X_DIR);
  }
}

void inline Motors::setUpY(MouvementQueue &mq)
{
  if (mq.getDy_state(mq.tail) == 2)
  {
    PORTB |= _BV(PIN_Y_DIR);
  }
  else
  {
    PORTB &= ~_BV(PIN_Y_DIR);
  }
}

void Motors::setUpZ(MouvementQueue &mq)
{
  if (mq.getDz_state(mq.tail) == 1)
  {
    PORTL &= ~(_BV(PIN_Z1_DIR) | _BV(PIN_Z2_DIR));
  }
  else
  {
    PORTL |= (_BV(PIN_Z1_DIR) | _BV(PIN_Z2_DIR));
  }
  setTimer1(mq_tail.imp_start_z);
  Flags::setFlag_motor_z_activated(1);
}

void Motors::setUpE(MouvementQueue &mq)
{
  if (mq.getDe_state(mq.tail) == 1)
  {
    PORTL &= ~(_BV(PIN_E_DIR));
  }
  else
  {
    PORTL |= (_BV(PIN_E_DIR));
  }
  setTimer1(VELOCITY_E);
  Flags::setFlag_motor_activated(1);
  mq_tail.step_e = 0;
}

void inline Motors::moveX(MouvementQueue &mq)
{
  if (mq_tail.step_xy < mq_tail.dx)
  {
    if (mq_tail.front_edge)
    {
      mq_tail.front_edge = 0;
      mq_tail.step_xy++;
      PORTB |= _BV(PIN_X_STEP);
    }
    else
    {
      mq_tail.front_edge = 1;
      PORTB &= ~_BV(PIN_X_STEP);
#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
      accelerationFactor++;
      if (accelerationFactor == ACCELERATION_FACTOR)
      {
        accelerateXY(mq);
        accelerationFactor = 0;
      }
#else
      accelerateXY(mq);
#endif
    }
  }
  else
  {
    // Setting OFF the TIMER_1
    stopTimer1();
    PORTB &= ~_BV(PIN_X_STEP);
    accelerationFactor = 0;
    Flags::setFlag_motor_activated(0);
    mq.removeAvailable_mouvement();
    mq.incrementTail();
    if (mq.getAvailable_mouvement())
    {
      mouvementSorter(mq);
    }
    if (Flags::getFlag_machine() == 2)
    {
      Flags::setFlag_machine(RECEIVING);
    }
  }
}

void inline Motors::moveY(MouvementQueue &mq)
{
  if (mq_tail.step_xy < mq_tail.dy)
  {
    if (mq_tail.front_edge)
    {
      mq_tail.front_edge = 0;
      mq_tail.step_xy++;
      PORTB |= _BV(PIN_Y_STEP);
    }
    else
    {
      mq_tail.front_edge = 1;
      PORTB &= ~_BV(PIN_Y_STEP);
#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
      accelerationFactor++;
      if (accelerationFactor == ACCELERATION_FACTOR)
      {
        accelerateXY(mq);
        accelerationFactor = 0;
      }
#else
      accelerateXY(mq);
#endif
    }
  }
  else
  {
    // Setting OFF the TIMER_1
    stopTimer1();
    PORTB &= ~_BV(PIN_Y_STEP);
    accelerationFactor = 0;
    Flags::setFlag_motor_activated(0);
    mq.removeAvailable_mouvement();
    mq.incrementTail();
    if (mq.getAvailable_mouvement())
    {
      mouvementSorter(mq);
    }
    if (Flags::getFlag_machine() == 2)
    {
      Flags::setFlag_machine(RECEIVING);
    }
  }
}

void inline Motors::moveXY(MouvementQueue &mq)
{
  // First case if dx is greater than dy
  if (mq.getDxDyCompareResult(mq.tail))
  {
    if (mq_tail.step_xy < mq.getDx(mq.tail))
    {
      if (mq_tail.front_edge)
      {
        mq_tail.front_edge = 0;
        mq_tail.step_xy++;
        mq_tail.over_xy += mq.getDy(mq.tail);
        if (mq_tail.over_xy >= mq.getDx(mq.tail))
        {
          mq_tail.over_xy -= mq.getDx(mq.tail);
          PORTB |= (_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
          FLAG_over_greater_dx = 1;
        }
        else
        {
          PORTB |= _BV(PIN_X_STEP);
          FLAG_over_greater_dx = 0;
        }
      }
      else
      {
        mq_tail.front_edge = 1;
        if (FLAG_over_greater_dx)
        {
          PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
        }
        else
        {
          PORTB &= ~_BV(PIN_X_STEP);
        }
#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
        accelerationFactor++;
        if (accelerationFactor == ACCELERATION_FACTOR)
        {
          accelerateXY(mq);
          accelerationFactor = 0;
        }
#else
        accelerateXY(mq);
#endif
      }
    }
    else
    {
      // Setting OFF the TIMER_1
      stopTimer1();
      PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
      accelerationFactor = 0;
      Flags::setFlag_motor_activated(0);
      mq.removeAvailable_mouvement();
      mq.incrementTail();
      if (mq.getAvailable_mouvement())
      {
        mouvementSorter(mq);
      }
      if (Flags::getFlag_machine() == 2)
      {
        Flags::setFlag_machine(RECEIVING);
      }
    }
  }
  // Second case if dy is greater than dx
  else
  {
    if (mq_tail.step_xy < mq.getDy(mq.tail))
    {
      if (mq_tail.front_edge)
      {
        mq_tail.front_edge = 0;
        mq_tail.step_xy++;
        mq_tail.over_xy += mq.getDx(mq.tail);
        if (mq_tail.over_xy >= mq.getDy(mq.tail))
        {
          mq_tail.over_xy -= mq.getDy(mq.tail);
          PORTB |= (_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
          FLAG_over_greater_dy = 1;
        }
        else
        {
          PORTB |= _BV(PIN_Y_STEP);
          FLAG_over_greater_dy = 0;
        }
      }
      else
      {
        mq_tail.front_edge = 1;
        if (FLAG_over_greater_dy)
        {
          PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
        }
        else
        {
          PORTB &= ~_BV(PIN_Y_STEP);
        }

#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
        accelerationFactor++;
        if (accelerationFactor == ACCELERATION_FACTOR)
        {
          accelerateXY(mq);
          accelerationFactor = 0;
        }
#else
        accelerateXY(mq);
#endif
      }
    }
    else
    {
      // Setting OFF the TIMER_1
      stopTimer1();
      PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
      accelerationFactor = 0;
      Flags::setFlag_motor_activated(0);
      mq.removeAvailable_mouvement();
      mq.incrementTail();
      if (mq.getAvailable_mouvement())
      {
        mouvementSorter(mq);
      }
      if (Flags::getFlag_machine() == 2)
      {
        Flags::setFlag_machine(RECEIVING);
      }
    }
  }
}

void inline Motors::moveXE(MouvementQueue &mq)
{
  if (mq_tail.step_xy < mq_tail.dx)
  {
    if (mq_tail.front_edge)
    {
      fMoveExtruder(mq);
      mq_tail.front_edge = 0;
      mq_tail.step_xy++;
      PORTB |= _BV(PIN_X_STEP);
    }
    else
    {
      mq_tail.front_edge = 1;
      PORTB &= ~_BV(PIN_X_STEP);
#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
      accelerationFactor++;
      if (accelerationFactor == ACCELERATION_FACTOR)
      {
        accelerateXY(mq);
        accelerationFactor = 0;
      }
#else
      accelerateXY(mq);
#endif
      fStopExtruder(mq);
    }
  }
  else
  {
    // Setting OFF the TIMER_1
    stopTimer1();
    PORTB &= ~_BV(PIN_X_STEP);
    accelerationFactor = 0;
    Flags::setFlag_motor_activated(0);
    mq.removeAvailable_mouvement();
    mq.incrementTail();
    if (mq.getAvailable_mouvement())
    {
      mouvementSorter(mq);
    }
    if (Flags::getFlag_machine() == 2)
    {
      Flags::setFlag_machine(RECEIVING);
    }
  }
}

void inline Motors::moveYE(MouvementQueue &mq)
{
  if (mq_tail.step_xy < mq_tail.dy)
  {
    if (mq_tail.front_edge)
    {
      fMoveExtruder(mq);
      mq_tail.front_edge = 0;
      mq_tail.step_xy++;
      PORTB |= _BV(PIN_Y_STEP);
    }
    else
    {
      mq_tail.front_edge = 1;
      PORTB &= ~_BV(PIN_Y_STEP);
#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
      accelerationFactor++;
      if (accelerationFactor == ACCELERATION_FACTOR)
      {
        accelerateXY(mq);
        accelerationFactor = 0;
      }
#else
      accelerateXY(mq);
#endif
      fStopExtruder(mq);
    }
  }
  else
  {
    // Setting OFF the TIMER_1
    stopTimer1();
    PORTB &= ~_BV(PIN_Y_STEP);
    accelerationFactor = 0;
    Flags::setFlag_motor_activated(0);
    mq.removeAvailable_mouvement();
    mq.incrementTail();
    if (mq.getAvailable_mouvement())
    {
      mouvementSorter(mq);
    }
    if (Flags::getFlag_machine() == 2)
    {
      Flags::setFlag_machine(RECEIVING);
    }
  }
}

void inline Motors::moveXYE(MouvementQueue &mq)
{
  // First case if dx is greater than dy
  if (mq.getDxDyCompareResult(mq.tail))
  {
    if (mq_tail.step_xy < mq.getDx(mq.tail))
    {
      if (mq_tail.front_edge)
      {
        fMoveExtruder(mq);
        mq_tail.front_edge = 0;
        mq_tail.step_xy++;
        mq_tail.over_xy += mq.getDy(mq.tail);
        if (mq_tail.over_xy >= mq.getDx(mq.tail))
        {
          mq_tail.over_xy -= mq.getDx(mq.tail);
          PORTB |= (_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
          FLAG_over_greater_dx = 1;
        }
        else
        {
          PORTB |= _BV(PIN_X_STEP);
          FLAG_over_greater_dx = 0;
        }
      }
      else
      {
        mq_tail.front_edge = 1;
        if (FLAG_over_greater_dx)
        {
          PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
        }
        else
        {
          PORTB &= ~_BV(PIN_X_STEP);
        }
#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
        accelerationFactor++;
        if (accelerationFactor == ACCELERATION_FACTOR)
        {
          accelerateXY(mq);
          accelerationFactor = 0;
        }
#else
        accelerateXY(mq);
#endif

        fStopExtruder(mq);
      }
    }
    else
    {
      // Setting OFF the TIMER_1
      stopTimer1();
      PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
      accelerationFactor = 0;
      Flags::setFlag_motor_activated(0);
      mq.removeAvailable_mouvement();
      mq.incrementTail();
      if (mq.getAvailable_mouvement())
      {
        mouvementSorter(mq);
      }
      if (Flags::getFlag_machine() == 2)
      {
        Flags::setFlag_machine(RECEIVING);
      }
    }
  }
  // Second case if dy is greater than dx
  else
  {
    if (mq_tail.step_xy < mq.getDy(mq.tail))
    {
      if (mq_tail.front_edge)
      {
        fMoveExtruder(mq);
        mq_tail.front_edge = 0;
        mq_tail.step_xy++;
        mq_tail.over_xy += mq.getDx(mq.tail);
        if (mq_tail.over_xy >= mq.getDy(mq.tail))
        {
          mq_tail.over_xy -= mq.getDy(mq.tail);
          PORTB |= (_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
          FLAG_over_greater_dy = 1;
        }
        else
        {
          PORTB |= _BV(PIN_Y_STEP);
          FLAG_over_greater_dy = 0;
        }
      }
      else
      {
        mq_tail.front_edge = 1;
        if (FLAG_over_greater_dy)
        {
          PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
        }
        else
        {
          PORTB &= ~_BV(PIN_Y_STEP);
        }

#if _ACCELERATION_REDUCTOR == 1 && ACCELERATION_FACTOR > 1
        accelerationFactor++;
        if (accelerationFactor == ACCELERATION_FACTOR)
        {
          accelerateXY(mq);
          accelerationFactor = 0;
        }
#else
        accelerateXY(mq);
#endif
        fStopExtruder(mq);
      }
    }
    else
    {
      // Setting OFF the TIMER_1
      stopTimer1();
      PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
      accelerationFactor = 0;
      Flags::setFlag_motor_activated(0);
      mq.removeAvailable_mouvement();
      mq.incrementTail();
      if (mq.getAvailable_mouvement())
      {
        mouvementSorter(mq);
      }
      if (Flags::getFlag_machine() == 2)
      {
        Flags::setFlag_machine(RECEIVING);
      }
    }
  }
}

inline void Motors::moveZ(MouvementQueue &mq)
{

  if (mq_tail.front_edge)
  {
    mq_tail.front_edge = !mq_tail.front_edge;
    mq_tail.step_z++;

    if (Flags::getFlag_automatic_bed_leveling() && !(PINC && _BV(PIN_AUTOLEVELING_SENSOR)))
    {

      PORTL &= ~(_BV(PIN_Z1_STEP) | _BV(PIN_Z2_STEP));
      stopTimer1();
      Flags::setFlag_motor_z_activated(0);

      Flags::setFlag_automatic_bed_leveling(0);
#ifdef _ACCELERATION_REDUCTOR_Z
      accelerationFactor = 0;
#endif
      sendData(mq_tail.step_z);
      jumpLine();
      
      if (mq.getDx_state(mq.tail) || mq.getDy_state(mq.tail))
      {
        mq_tail.front_edge = 1;
      }
      else
      {
        mq.removeAvailable_mouvement();
        mq.incrementTail();
      }
      return;
    }

    if (mq.getDz(mq.tail) < mq_tail.step_z)
    {
      PORTL &= ~(_BV(PIN_Z1_STEP) | _BV(PIN_Z2_STEP));
      stopTimer1();
      Flags::setFlag_motor_z_activated(0);

#ifdef _ACCELERATION_REDUCTOR_Z
      accelerationFactor = 0;
#endif

      if (mq.getDx_state(mq.tail) || mq.getDy_state(mq.tail))
      {
        mq_tail.front_edge = 1;
        Flags::setFlag_motor_activated(1);
        setTimer1(mq.getImp_start(mq.tail));
      }
      else
      {
        mq.removeAvailable_mouvement();
        mq.incrementTail();
        if (mq.getAvailable_mouvement())
        {
          mouvementSorter(mq);
        }
        if (Flags::getFlag_machine() == 2)
        {
          Flags::setFlag_machine(RECEIVING);
        }
      }
      return;
    }
    else
    {
#ifdef _ACCELERATION_REDUCTOR_Z
      accelerationFactor++;
      if (accelerationFactor == 1)
      {
        accelerateZ(mq);
        accelerationFactor = 0;
      }
#else
      accelerateZ(mq);
#endif
    }
  }
  else
  {
    mq_tail.front_edge = !mq_tail.front_edge;
  }

  PORTL ^= (_BV(PIN_Z1_STEP) | _BV(PIN_Z2_STEP));
}

inline void Motors::moveE(MouvementQueue &mq)
{

  if (mq_tail.front_edge)
  {
    mq_tail.front_edge = !mq_tail.front_edge;
    mq_tail.step_e++;

    if (mq.getDe(mq.tail) < mq_tail.step_e)
    {
      PORTL &= ~(_BV(PIN_E_STEP));
      PORTL &= ~(_BV(PIN_E_DIR));
      stopTimer1();

      Flags::setFlag_motor_activated(0);
      mq.removeAvailable_mouvement();
      mq.incrementTail();
      if (mq.getAvailable_mouvement())
      {
        mouvementSorter(mq);
      }
      if (Flags::getFlag_machine() == 2)
      {
        Flags::setFlag_machine(RECEIVING);
      }
      return;
    }
  }
  else
  {
    mq_tail.front_edge = !mq_tail.front_edge;
  }

  PORTL ^= (_BV(PIN_E_STEP));
}