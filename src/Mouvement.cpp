#include "Mouvement.h"
#include "Sending.h"

void Mouvement::calculateAccelerationXaxis(uint16_t &future_imp_start)
{
#ifdef _ACCELERATION_REDUCTOR
// If acceleration is equal to 1
#if (ACCELERATION != 1)
  acceleration_distance =
      ((imp_start - imp_value) / acceleration) * ACCELERATION_FACTOR;
#else

  if (imp_start >= imp_value)
  {
    acceleration_distance = (imp_start - imp_value) * ACCELERATION_FACTOR;
  }
  else
  {
    acceleration_distance = 0;
  }
  if (imp_finish >= imp_value)
  {
    deceleration_distance = (imp_finish - imp_value) * ACCELERATION_FACTOR;
    deceleration_starting_point = abs(dx - deceleration_distance);
  }
  else
  {
    deceleration_distance = 0;
    deceleration_starting_point = dx;
  }

#endif
// End if acceleration is not equal 1
#else
  acceleration_distance = ((imp_start - imp_value) / acceleration);
#endif

  // Checking if we have enough distance to accelerate then decelerate
  if ((dx) < (acceleration_distance + deceleration_distance))
  {
    // Checking if it's an acceleration or deceleration
    if (imp_finish < imp_start)
    {
      // It's an acceleration
      acceleration_distance = imp_start - imp_finish;
      // There is no deceleration
      deceleration_starting_point = dx;
      // Checking if we can accelerate till the imp_finish
      if ((dx) < acceleration_distance)
      {
        // No we can't so we need to calculate what speed we will be at
        acceleration_distance = dx;
        future_imp_start = imp_start - dx;
      }
      else
      {
        // Yes we can
        future_imp_start = imp_finish;
        imp_value = imp_finish;
      }
    }
    else
    {
      // It's a decceleration
      deceleration_distance = imp_finish - imp_start;
      // There is no acceleration
      acceleration_distance = 0;
      // Checking if we can decelerate till the imp_finish
      if ((dx) < deceleration_distance)
      {
        // No we can't so we need to calculate what speed we will be at
        deceleration_starting_point = 0;
        future_imp_start = imp_start + dx;
      }
      else
      {
        // Yes we can
        deceleration_starting_point = dx - deceleration_distance;
        imp_value = imp_finish;
        future_imp_start = imp_finish;
      }
    }
  }
  else
  {
    future_imp_start = imp_finish;
  }
}

void Mouvement::calculateAccelerationYaxis(uint16_t &future_imp_start)
{
#ifdef _ACCELERATION_REDUCTOR
// If acceleration is equal to 1
#if (ACCELERATION != 1)
  acceleration_distance =
      ((imp_start - imp_value) / acceleration) * ACCELERATION_FACTOR;
#else
  if (imp_start >= imp_value)
  {
    acceleration_distance = (imp_start - imp_value) * ACCELERATION_FACTOR;
  }
  else
  {
    acceleration_distance = 0;
  }
  if (imp_finish >= imp_value)
  {
    deceleration_distance = (imp_finish - imp_value) * ACCELERATION_FACTOR;
    deceleration_starting_point = abs(dy - deceleration_distance);
  }
  else
  {
    deceleration_distance = 0;
    deceleration_starting_point = dy;
  }

#endif
// End if acceleration is not equal 1
#else
  acceleration_distance = ((imp_start - imp_value) / acceleration);
#endif

  // Checking if we have enough distance to accelerate then decelerate
  if ((dy) < (acceleration_distance + deceleration_distance))
  {
    // Checking if it's an acceleration or deceleration
    if (imp_finish < imp_start)
    {
      // It's an acceleration
      acceleration_distance = imp_start - imp_finish;
      // There is no deceleration
      deceleration_starting_point = dy;
      // Checking if we can accelerate till the imp_finish
      if ((dy) < acceleration_distance)
      {
        // No we can't so we need to calculate what speed we will be at
        acceleration_distance = dy;
        future_imp_start = imp_start - dy;
      }
      else
      {
        // Yes we can
        future_imp_start = imp_finish;
        imp_value = imp_finish;
      }
    }
    else
    {
      // It's a decceleration
      deceleration_distance = imp_finish - imp_start;
      // There is no acceleration
      acceleration_distance = 0;
      // Checking if we can decelerate till the imp_finish
      if ((dy) < deceleration_distance)
      {
        // No we can't so we need to calculate what speed we will be at
        deceleration_starting_point = 0;
        future_imp_start = imp_start + dy;
      }
      else
      {
        // Yes we can
        deceleration_starting_point = dy - deceleration_distance;
        imp_value = imp_finish;
        future_imp_start = imp_finish;
      }
    }
  }
  else
  {
    future_imp_start = imp_finish;
  }
}

void Mouvement::calculateAccelerationZaxis()
{
#ifdef _ACCELERATION_REDUCTOR_Z
// If acceleration is equal to 1
#if (ACCELERATION_Z != 1)
  acceleration_distance_z =
      ((imp_start_z - imp_value_z) / acceleration_z) * ACCELERATION_FACTOR;
#else
  acceleration_distance_z = abs((imp_start_z - imp_value_z) * ACCELERATION_FACTOR);
#endif
// End if acceleration is not equal 1
#else
  acceleration_distance_z = ((imp_start_z - imp_value_z) / acceleration_z);
#endif

  if (dz < (acceleration_distance_z * 2))
  {
    acceleration_distance_z = dz / 2;
  }
  deceleration_distance_z = abs(dz - acceleration_distance_z);
}