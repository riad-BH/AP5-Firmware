#if !defined(H_MOUVEMENT)
#define H_MOUVEMENT

#include "Arduino.h"
#include "Sending.h"
#include "Setting.h"

enum MouvementStates : uint8_t
{
  ms_null,
  ms_x,
  ms_y,
  ms_xy,
  ms_e,
  ms_xe,
  ms_ye,
  ms_xye,
  ms_z,
  ms_xz,
  ms_yz,
  ms_xyz,
  ms_ze,
  ms_xez,
  ms_yez,
  ms_xyez
};

class Mouvement
{

public:
  uint8_t mouvement_state_selection = ms_null;

  int32_t dx = 0;
  int32_t dy = 0;
  int32_t dz = 0;
  int32_t de = 0;

  // 0 = null, 1 = positive, 2 = negative
  uint8_t dx_state = 0;
  // 0 = null, 1 = positive, 2 = negative
  uint8_t dy_state = 0;
  // 0 = null, 1 = positive, 2 = negative
  uint8_t dz_state = 0;
  // 0 = null, 1 = positive, 2 = negative
  uint8_t de_state = 0;

  bool dx_greater_dy = true;

  uint16_t imp_start = IMP_START;
  uint16_t imp_start_x16 = IMP_START * 16;

  uint16_t imp_value = IMP_VALUE;
  uint16_t imp_value_x16 = IMP_VALUE * 16;

  uint16_t imp_finish = IMP_START;

  uint8_t next_angle = 0;

  uint16_t acceleration = ACCELERATION;
  uint16_t acceleration_x16 = ACCELERATION * 16;
  uint16_t acceleration_distance = 0;
  uint16_t deceleration_distance = 0;
  uint16_t deceleration_starting_point = 0;

  // Extruder speed
  uint8_t extruder_speed = EXTRUDER_SPEED;

  uint16_t imp_start_z = JERK_Z;

  uint16_t imp_value_z = VELOCITY_Z;
  uint16_t imp_value_z_x16 = VELOCITY_Z * 16;

  uint16_t acceleration_z = ACCELERATION_Z;
  uint16_t acceleration_z_x16 = ACCELERATION_Z * 16;

  uint16_t acceleration_distance_z = 0;
  uint16_t deceleration_distance_z = 0;

  // Variable used for the impulsion value
  // Variable's format : "microseconds * 16"
  uint16_t imp_size = (IMP_START * 16);
  // Variable used for the impulsion value for Z axis
  // Variable's format : "microseconds * 16"
  uint16_t imp_size_z = (JERK_Z * 16);

  // Over bresenham
  uint16_t over_xy = 0;
  // X Y motor's steps for bresenham
  uint16_t step_xy = 0;
  // Extruder motor's steps
  uint16_t step_e = EXTRUDER_SPEED;
  // Z axis motor's steps
  uint16_t step_z = 0;

  // For ISR a front edge
  uint8_t front_edge = 1;

  inline void resetValues()
  {

    dx = 0;
    dy = 0;
    dz = 0;
    de = 0;

    dx_state = 0;
    dy_state = 0;
    dz_state = 0;
    de_state = 0;

    // Over bresenham
    over_xy = 0;
    // X Y motor's steps for bresenham
    step_xy = 0;
    // Extruder motor's steps
    step_e = EXTRUDER_SPEED;
    // Z axis motor's steps
    step_z = 0;

    mouvement_state_selection = ms_null;

    front_edge = 1;
  }

  void inline testDx()
  {

    if (dx < 0)
    {
      dx = -(dx);
      dx_state = 2;
    }
    else if (dx > 0)
    {
      dx_state = 1;
    }
  }

  void inline testDy()
  {

    if (dy < 0)
    {
      dy = -(dy);
      dy_state = 2;
    }
    else if (dy > 0)
    {
      dy_state = 1;
    }
  }

  void inline testDz()
  {

    if (dz < 0)
    {
      dz = -(dz);
      dz_state = 2;
    }
    else if (dz > 0)
    {
      dz_state = 1;
    }
  }

  void inline testDe()
  {
    if (de < 0)
    {
      de = -(de);
      de_state = 2;
    }
    else if (de > 0)
    {
      de_state = 1;
    }
  }

  // returns 1 if Dx is greater or equals Dy
  bool inline compareDxDy()
  {
    if (dx >= dy)
    {
      dx_greater_dy = true;
      return true;
    }
    dx_greater_dy = false;
    return false;
  }

  void calculateAccelerationXaxis(uint16_t &);

  void calculateAccelerationYaxis(uint16_t &);

  void calculateAccelerationZaxis();

  void inline mouvementSelection()
  {
    if (dx_state)
    {
      mouvement_state_selection += ms_x;
    }
    if (dy_state)
    {
      mouvement_state_selection += ms_y;
    }
    if (de_state)
    {
      mouvement_state_selection += ms_e;
    }
    if (dz_state)
    {
      mouvement_state_selection += ms_z;
    }
  }
};

#endif // H_MOUVEMENT
