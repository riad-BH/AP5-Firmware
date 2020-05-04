#include "Flags.h"

// Flag is set to 1 when motors are moving
volatile uint8_t Flags::flag_motor_activated;
// Flag is set to 1 if Z motor is activated
volatile uint8_t Flags::flag_motor_z_activated = 0;
// Flag is set to one if automatic bed leveling is activated
volatile uint8_t Flags::flag_automatic_bed_leveling = 0;
// Flag Machine : 0 = Receiving / 1 = Processing / 2 = Execution
volatile uint8_t Flags::flag_machine = RECEIVING;