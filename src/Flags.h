#ifndef H_FLAGS
#define H_FLAGS

// Is array 1 or 2 begin processed and executed
volatile uint8_t FLAG_array1_or_array2 = 1;

// Flag is set to 1 when motors are moving
volatile uint8_t FLAG_motorsActivated = 0;

// Flag is set to one if automatic bed leveling is activated
volatile uint8_t FLAG_automaticBedLeveling = 0;

// Flag is set to 1 if Z motor is activated
volatile uint8_t FLAG_motor_Z_acivated = 0;

// Flag is set to :
//# 0 == RX_array1 empty
//# 1 == RX_array1 full
//# 2 == RX_array1 processed
uint8_t FLAG_RX_array1_state = EMPTY;
// Flag is set to :
//# 0 == RX_array2 empty
//# 1 == RX_array2 full
//# 2 == RX_array2 processed
uint8_t FLAG_RX_array2_state = EMPTY;

// Flag Machine : 0 = Receiving / 1 = Processing / 2 = Execution
uint8_t FLAG_machine = RECEIVING;

// Flag that indicates that a data has ben recieved and it's ready to be
// processed
volatile uint8_t FLAG_RX = 0;

#endif // H_FLAGS
