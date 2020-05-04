#ifndef H_FLAGS
#define H_FLAGS

#include "Arduino.h"
#include "ConstDefines.h"
#include "Setting.h"

class Flags
{

private:
  // Flag is set to 1 when motors are moving
  static volatile uint8_t flag_motor_activated;
  // Flag is set to 1 if Z motor is activated
  static volatile uint8_t flag_motor_z_activated;
  // Flag is set to one if automatic bed leveling is activated
  static volatile uint8_t flag_automatic_bed_leveling;
  // Flag Machine : 0 = Receiving / 1 = Processing / 2 = Execution
  static volatile uint8_t flag_machine;

public:
  inline static volatile const uint8_t &getFlag_motor_activated()
  {
    return flag_motor_activated;
  }
  inline static void setFlag_motor_activated(const uint8_t &_flag_motor_activated)
  {
    flag_motor_activated = _flag_motor_activated;
  }

  inline static const volatile uint8_t &getFlag_motor_z_activated()
  {
    return flag_motor_z_activated;
  }

  inline static void setFlag_motor_z_activated(const uint8_t &_flag_motor_z_activated)
  {
    flag_motor_z_activated = _flag_motor_z_activated;
  }

  inline static const uint8_t getFlag_automatic_bed_leveling()
  {
    return flag_automatic_bed_leveling;
  }
  inline static void
  setFlag_automatic_bed_leveling(const uint8_t &_flag_automatic_bed_leveling)
  {
    flag_automatic_bed_leveling = _flag_automatic_bed_leveling;
  }

  inline const static uint8_t getFlag_machine() { return flag_machine; }

  inline static void setFlag_machine(const uint8_t &_flag_machine)
  {
    flag_machine = _flag_machine;
  }
};

#endif // H_FLAGS
