#include "Motors.h"

/************************************************/
// X axis steps per milimeter
uint16_t spmX = STEP_PER_MILLIMETER_X;
// Y axis steps per milimeter
uint16_t spmY = STEP_PER_MILLIMETER_Y;
// Z axis steps per milimeter
uint16_t spmZ = STEP_PER_MILLIMETER_Z;
/************************************************/

/*************************************************************************************************/
// Copy of dx
volatile int32_t _dx;
// Copy of dy
volatile int32_t _dy;
// Copy of  dz * 2
volatile int32_t _dz;
// Copy of  de * 2
volatile int32_t _de;
/************************************************/
// If dx is negative the flag is set to one
volatile uint8_t _FLAG_dx_is_negative;
// If dy is negative the flag is set to one
volatile uint8_t _FLAG_dy_is_negative;
/************************************************/

/*************** Local Variables ***************/
// Copy of accelDistance_1
volatile static uint16_t _accelDistance_1;
// Copy of accelDistance_2
volatile static uint16_t _accelDistance_2;
// Copy of accelDistance_1_dz
volatile static uint16_t _accelDistance_1_dz;
// Copy of accelDistance_2_dz
volatile static uint16_t _accelDistance_2_dz;

/************************************************/
// Extruder motor's steps
volatile static uint16_t extruderStep = 0;
// Z axis motor's steps
volatile static uint16_t zStep = 0;
// Flag is set to 1 if Z motor is activated
volatile static uint8_t FLAG_motor_Z_acivated = 0;
/************************************************/
// For ISR a front edge
volatile static uint8_t frontEdge = 1;
// For ISR a front edge for Z axis
volatile static uint8_t frontEdge_dz = 1;
// Over bresenham
volatile static uint16_t over = 0;
// X Y motor's steps for bresenham
volatile uint16_t step = 0;
// Copy of FLAG_array1_or_array2
volatile static uint8_t _FLAG_array1_or_array2;
// Variable used for the impulsion value
// Variable's format : "microseconds * 16"
volatile static uint16_t impSize = (IMP_START * 16);
// Variable used for the impulsion value for Z axis
// Variable's format : "microseconds * 16"
volatile static uint16_t impSize_Z = (JERK_Z * 16);
/************************************************/
// Flags for Motor's mouvement ISR
volatile static uint8_t FLAG_over_greater_dx = 0;
// Flags for Motor's mouvement ISR
volatile static uint8_t FLAG_over_greater_dy = 0;
/************************************************/
// Copy of the impulsion size in microseconds
volatile static uint16_t _impValue = 0;
/************************************************/
// Copy of Flag Extruder if there is extrusion or not
volatile static uint8_t _FLAG_extruder = 0;
/************************************************/
// Copy of Acceleration value x 16
volatile static uint16_t _acceleration;
// Copy of Acceleration value x 16 for Z axis
volatile static uint16_t _acceleration_dz;
/************************************************/
// Acceleration factor value : (1 / accelerationFactor) * _acceleration
volatile static uint8_t accelerationFactor = 0;
/************************************************/
// Copy of velocity_dz
volatile static uint16_t _velocity_dz = VELOCITY_Z * 16;
/*************************************************************************************************/
/*************** Extern Variables ***************/
// Extruder speed
extern uint8_t extruderSpeed;
// Flag Extruder if there is extrusion or not
extern uint8_t FLAG_extruder;
/************************************************/
// Is array 1 or 2 begin processed and executed
extern volatile uint8_t FLAG_array1_or_array2;
// Flag is set to 1 when motors are moving
extern volatile uint8_t FLAG_motorsActivated;
/************************************************/
// Flag Machine : 0 = Receiving / 1 = Processing / 2 = Execution
extern uint8_t FLAG_machine;
/************************************************/
// Flag is set to :
//# 0 == RX_array1 empty
//# 1 == RX_array1 full
//# 2 == RX_array1 processed
extern uint8_t FLAG_RX_array1_state;
// Flag is set to :
//# 0 == RX_array2 empty
//# 1 == RX_array2 full
//# 2 == RX_array2 processed
extern uint8_t FLAG_RX_array2_state;
/************************************************/
// If dx is negative the flag is set to one
extern volatile uint8_t FLAG_dx_is_negative;
// If dy is negative the flag is set to one
extern volatile uint8_t FLAG_dy_is_negative;
/************************************************/
// Distance from 0 to achieve impValue starting with impStart
extern uint16_t accelDistance_1;
// Distance with impValue
extern uint16_t accelDistance_2;
// Distance to decelerate
extern uint16_t accelDistance_3;
// Acceleration value
extern uint8_t acceleration;
// Acceleration distance for Z axis
extern uint16_t accelDistance_1_dz;
// Distance until deccelaration for Z axis
extern uint16_t accelDistance_2_dz;
// Acceleration value for Z axis
extern uint8_t acceleration_dz;
/************************************************/
// Impulsion size at the start in microseconds
extern uint16_t impStart;
extern uint16_t impValue;
/************************************************/
extern int32_t dx;
extern int32_t dy;
extern int32_t dz;
extern int32_t de;
/************************************************/
// Flag set on if there is an extrusion
extern uint8_t FLAG_extrusion_for_timer;
/************************************************/
// Flag is set to :
// 0 if dz = 0
// 1 if dz positif
// 2 if dz negative
extern uint8_t FLAG_dz_state;
/************************************************/

/*************** Extern Function ***************/
extern void setTimer1(uint16_t);
extern void setTimer3(uint16_t);
/************************************************/
// Function to send data
// Function to send data USART_0
void sendData(String);
void sendData(float *);
void sendData(uint8_t *);
void sendData(int8_t *);
void sendData(uint16_t *);
void sendData(int16_t *);
void sendData(uint32_t *);
void sendData(int32_t *);
void sendData(int8_t);
void sendData(int16_t);
void sendData(int32_t);
/************************************************/
#define fSetUpXYE()                                                            \
  frontEdge = 1;                                                               \
  _dx = dx;                                                                    \
  _dy = dy;                                                                    \
  _acceleration = (uint16_t)((uint16_t)acceleration * 16);                     \
  _accelDistance_1 = accelDistance_1;                                          \
  _accelDistance_2 = accelDistance_2;                                          \
  _FLAG_array1_or_array2 = FLAG_array1_or_array2;                              \
  _FLAG_dx_is_negative = FLAG_dx_is_negative;                                  \
  _FLAG_dy_is_negative = FLAG_dy_is_negative;                                  \
  FLAG_motorsActivated = 1;                                                    \
  _impValue = (uint16_t)(impValue * 16);                             \
  _FLAG_extruder = FLAG_extruder;                                              \
  FLAG_machine = 0;                                                            \
  dx = 0;                                                                      \
  dy = 0
/******************************************************************************/

/******************************************************************************/
#define fAcceleration()                                                        \
  if (step < _accelDistance_1) {                                               \
                                                                               \
    impSize = impSize - _acceleration;                                         \
                                                                               \
    OCR1A = impSize;                                                           \
  }                                                                            \
                                                                               \
  else if (step < _accelDistance_2 && _accelDistance_1 < step) {               \
    impSize = _impValue;                                                       \
    OCR1A = impSize;                                                           \
  }                                                                            \
                                                                               \
  else if (_accelDistance_2 < step) {                                          \
    impSize = impSize + _acceleration;                                         \
    OCR1A = impSize;                                                           \
  }

/******************************************************************************/

/******************************************************************************/
#define fAccelerationZ()                                                       \
  if (zStep < _accelDistance_1_dz) {                                           \
    impSize_Z = impSize_Z - _acceleration_dz;                                  \
                                                                               \
    OCR3A = impSize_Z;                                                         \
                                                                               \
  }                                                                            \
                                                                               \
  else if (zStep < _accelDistance_2_dz && _accelDistance_1_dz < zStep) {       \
    impSize_Z = _velocity_dz;                                                  \
    OCR3A = impSize_Z;                                                         \
  }                                                                            \
                                                                               \
  else if (_accelDistance_2_dz < zStep) {                                      \
    impSize_Z = impSize_Z + _acceleration_dz;                                  \
    OCR3A = impSize_Z;                                                         \
  }

/******************************************************************************/

/************************************************/
/*
  * SETTING FUNCTION : SETS UP SOME SETTING FOR THE MOVE FUNCTION
*/
void fSettingUp() {

  if (FLAG_dx_is_negative) {
    PORTB |= _BV(PIN_X_DIR);
  } else {
    PORTB &= ~_BV(PIN_X_DIR);
  }

  if (FLAG_dy_is_negative) {
    PORTB |= _BV(PIN_Y_DIR);
  } else {
    PORTB &= ~_BV(PIN_Y_DIR);
  }

  if (FLAG_dz_state) {
    FLAG_motor_Z_acivated = 1;
    fSettingUpZ();
    while (FLAG_motor_Z_acivated) {
    }
    // impSize = (uint16_t)((uint16_t)impSize * 16);
    fSetUpXYE();
    setTimer1(impStart);
  } /*else if (FLAG_extrusion_for_timer != 0) {
    if(FLAG_extrusion_for_timer == 1){
      PORTL &= ~(_BV(PIN_E_DIR));
    }else if(FLAG_extrusion_for_timer == 2){
      PORTL |= (_BV(PIN_E_DIR));
    }
    fSettingUpE();
  }*/ else {
    // impSize = (uint16_t)((uint16_t)impSize * 16);
    fSetUpXYE();
    setTimer1(impStart);
  }
  // PORTL &=~ _BV(PIN_Z_STEP);
}
/************************************************/

/************************************************/
/*
  * MOVE FUNCTION : ACTIONS THE MOTORS X Y E
*/
void fMoveXYE() {

  // First case if dx is greater than dy
  if (_dx > _dy) {
    if (step < _dx) {
      if (frontEdge) {
#ifdef _USE_fMoveExtruder
        fMoveExtruder();
#else
        if (_FLAG_extruder) {
          extruderStep++;
          if (extruderStep == extruderSpeed) {
            PORTA ^= (_BV(PIN_E_STEP));
            extruderStep = 0;
          }
        }
#endif
        frontEdge = 0;
        step++;
        over += _dy;
        if (over >= _dx) {
          over -= _dx;
          PORTB |= (_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
          FLAG_over_greater_dx = 1;
        } else {
          PORTB |= _BV(PIN_X_STEP);
          FLAG_over_greater_dx = 0;
        }
      } else {
        frontEdge = 1;
        if (FLAG_over_greater_dx) {
          PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
        } else {
          PORTB &= ~_BV(PIN_X_STEP);
        }
#ifdef _ACCELERATION_REDUCTOR
        accelerationFactor++;
        if (accelerationFactor == ACCELERATION_FACTOR) {
          fAcceleration();
          accelerationFactor = 0;
        }
#else
        fAcceleration();
#endif
#ifdef _USE_fMoveExtruder
        fStopExtruder()
#endif
      }
    } else {
      // Setting OFF the TIMER_1
      TCCR1B = 0;
      TCNT1 = 0;
      PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
      fStopExtruder();
      step = 0;
      over = 0;
      // extruderStep = 0;
      accelerationFactor = 0;
      FLAG_motorsActivated = 0;
      if (_FLAG_array1_or_array2 == 1) {
        FLAG_RX_array1_state = EMPTY;
      } else {
        FLAG_RX_array2_state = EMPTY;
      }
    }
  }

  // Second case if dy is greater than dx
  else {
    if (step < _dy) {
      if (frontEdge) {
#ifdef _USE_fMoveExtruder
        fMoveExtruder();
#else
        if (_FLAG_extruder) {
          extruderStep++;
          if (extruderStep == extruderSpeed) {
            PORTA ^= (_BV(PIN_E_STEP));
            extruderStep = 0;
          }
        }
#endif
        frontEdge = 0;
        step++;
        over += _dx;
        if (over >= _dy) {
          over -= _dy;
          PORTB |= (_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
          FLAG_over_greater_dy = 1;
        } else {
          PORTB |= _BV(PIN_Y_STEP);
          FLAG_over_greater_dy = 0;
        }
      } else {
        frontEdge = 1;
        if (FLAG_over_greater_dy) {
          PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
        } else {
          PORTB &= ~_BV(PIN_Y_STEP);
        }
#ifdef _ACCELERATION_REDUCTOR
        accelerationFactor++;
        if (accelerationFactor == ACCELERATION_FACTOR) {
          fAcceleration();
          accelerationFactor = 0;
        }
#else
        fAcceleration();
#endif
#ifdef _USE_fMoveExtruder
        fStopExtruder()
#endif
      }
    } else {
      // Setting OFF the TIMER_1
      TCCR1B = 0;
      TCNT1 = 0;
      PORTB &= ~(_BV(PIN_X_STEP) | _BV(PIN_Y_STEP));
      fStopExtruder();
      step = 0;
      over = 0;
      // extruderStep = 0;
      accelerationFactor = 0;
      FLAG_motorsActivated = 0;
      if (_FLAG_array1_or_array2 == 1) {
        FLAG_RX_array1_state = EMPTY;
      } else {
        FLAG_RX_array2_state = EMPTY;
      }
    }
  }
}
/************************************************/

/************************************************/
/*
  * SETTING FUNCTION : SETS UP SOME SETTING FOR THE MOVE Z FUNCTION
*/
void fSettingUpZ() {
  _dz = dz;
  _accelDistance_1_dz = accelDistance_1_dz;
  _accelDistance_2_dz = accelDistance_2_dz;
  _acceleration_dz = uint16_t(acceleration_dz * 16);
  if (FLAG_dz_state == 1) {
    PORTL &= ~(_BV(PIN_Z1_DIR)|_BV(PIN_Z2_DIR));
  } else {
    PORTL |= (_BV(PIN_Z1_DIR)|_BV(PIN_Z2_DIR));
  }
  setTimer3(JERK_Z);
  dz = 0;
}
/************************************************/

/************************************************/
/*
  * MOVE FUNCTION : ACTIONS THE MOTOR Z
*/
void fMoveZ() {

   PORTL ^= (_BV(PIN_Z1_STEP)|_BV(PIN_Z2_STEP));
   
  if (frontEdge_dz) {
    frontEdge_dz = !frontEdge_dz;
    zStep++;
    if (zStep == _dz) {
      PORTL &= ~(_BV(PIN_Z1_STEP)|_BV(PIN_Z2_STEP));
      TIMSK3 = 0;
      TCNT3 = 0;
      TCCR3B = 0;
      zStep = 0;
      FLAG_motor_Z_acivated = 0;
      frontEdge_dz = 1;
#ifdef _ACCELERATION_REDUCTOR_Z
      accelerationFactor = 0;
#endif
    } else {
#ifdef _ACCELERATION_REDUCTOR_Z
      accelerationFactor++;
      if (accelerationFactor == 1) {
        fAccelerationZ();
        accelerationFactor = 0;
      }
#else
      fAccelerationZ();
#endif
    }

  } else {
    frontEdge_dz = !frontEdge_dz;
  }
}
/************************************************/
void fSettingUpE() {
  _de = de * 2;
  setTimer3(VELOCITY_E);
}
/************************************************/
void fMoveE() {
  PORTA ^= (_BV(PIN_E_STEP));
  extruderStep++;
  if (extruderStep == _de) {
    PORTA &= ~(_BV(PIN_E_STEP));
    PORTA &= ~(_BV(PIN_E_DIR));
    TIMSK3 = 0;
    TCNT3 = 0;
    TCCR3B = 0;
    extruderStep = 0;
    FLAG_extrusion_for_timer = 0;
  }
}
/************************************************/