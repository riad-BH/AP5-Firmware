#include "Acceleration.h"

// Jump line function
#ifdef _PROTEUS
#define jumpLine() sendData("\r")
#else
#define jumpLine() sendData("\n")
#endif

/************************************************/
// Acceleration distance for X & Y axis
uint16_t accelDistance_1 = 0;
// Distance until deccelaration for X & Y axis
uint16_t accelDistance_2 = 0;
// Acceleration value for X & Y axis
uint8_t acceleration = ACCELERATION;
/************************************************/
// Acceleration distance for Z axis
uint16_t accelDistance_1_dz = 0;
// Distance until deccelaration for Z axis
uint16_t accelDistance_2_dz = 0;
// Acceleration value for Z axis
uint8_t acceleration_dz = ACCELERATION_Z;
/************************************************/
// If dx is negative the flag is set to one
// 0 = positive
// 1 = negative
// 2 = null
volatile uint8_t FLAG_dx_is_negative = 0;
// If dy is negative the flag is set to one
// 0 = positive
// 1 = negative
// 2 = null
volatile uint8_t FLAG_dy_is_negative = 0;
/************************************************/

/*************** Extern Variables ***************/
extern uint16_t impStart;
extern uint16_t impValue;
extern uint16_t impControlableValue;
extern uint16_t jerk_z;
extern uint16_t velocity_z;
/************************************************/
// Flag is set to 1 if it's a G1 command
// Or if it's G0 command it is set to 0
extern uint8_t FLAG_G0_or_G1;
/************************************************/
// Flag is set to :
// 0 if dz = 0
// 1 if dz positif
// 2 if dz negative
uint8_t FLAG_dz_state = 0;
/************************************************/

/*************** Extern Function ***************/
// Function to send data
void sendData(String);
void sendData(float *);
void sendData(uint8_t *);
void sendData(int8_t *);
void sendData(uint16_t *);
void sendData(int16_t *);
void sendData(uint32_t *);
void sendData(int32_t *);
/************************************************/
void fAccelCompute(int32_t *dX, int32_t *dY) {
  FLAG_dx_is_negative = 0;
  FLAG_dy_is_negative = 0;

  if (FLAG_G0_or_G1) {
    impValue = impControlableValue;
  } else {
    impValue = IMP_VALUE_G0;
  }

  if (*dY < 0) {
    *dY = -(*dY);
    FLAG_dy_is_negative = 1;
  }

  if (*dX < 0) {
    *dX = -(*dX);
    FLAG_dx_is_negative = 1;
  }

  if ((*dX) >= (*dY) && (*dX) != 0) {

#ifdef _ACCELERATION_REDUCTOR
// If acceleration is equal to 1
#if (ACCELERATION != 1)
    accelDistance_1 =
        ((impStart - impValue) / acceleration) * ACCELERATION_FACTOR;
#else
    accelDistance_1 = abs((impStart - impValue) * ACCELERATION_FACTOR);
#endif
// End if acceleration is not equal 1
#else
    accelDistance_1 = ((impStart - impValue) / acceleration);
#endif

    if ((*dX) < (accelDistance_1 * 2)) {
      accelDistance_1 = (*dX) / 2;
    }
    accelDistance_2 = abs(*dX - accelDistance_1);

#ifdef _DEBUG
    sendData("dx >= dy");
    jumpLine();
    sendData(&accelDistance_1);
    jumpLine();
    sendData(&accelDistance_2);
    jumpLine();
    sendData("acceleration:  ");
    sendData(&acceleration);
    jumpLine();
#endif
  } else if ((*dY) > (*dX) && (*dY) != 0) {

#ifdef _ACCELERATION_REDUCTOR
#if (ACCELERATION != 1)
    accelDistance_1 =
        ((impStart - impValue) / acceleration) * ACCELERATION_FACTOR;
#else
    accelDistance_1 = abs((impStart - impValue) * ACCELERATION_FACTOR);
#endif
#else
    accelDistance_1 = ((impStart - impValue) / acceleration);
#endif

    if ((*dY) < (accelDistance_1 * 2)) {
      accelDistance_1 = (*dY) / 2;
    }
    accelDistance_2 = abs(*dY - accelDistance_1);

#ifdef _DEBUG
    sendData("dy > dx");
    jumpLine();
    sendData("acceleration:  ");
    sendData(&acceleration);
    jumpLine();
#endif
  }
}
/************************************************/

/************************************************/
void fAccelCompute(int32_t *dX, int32_t *dY, int32_t *dZ) {

  // Reset flags
  FLAG_dx_is_negative = 0;
  FLAG_dy_is_negative = 0;
  FLAG_dz_state = 0;

  if (FLAG_G0_or_G1) {
    impValue = impControlableValue;
  } else {
    impValue = IMP_VALUE_G0;
  }

  if (*dY < 0) {
    *dY = -(*dY);
    FLAG_dy_is_negative = 1;
  }

  if (*dX < 0) {
    *dX = -(*dX);
    FLAG_dx_is_negative = 1;
  }

  if ((*dX) >= (*dY) && (*dX) != 0) {

#ifdef _ACCELERATION_REDUCTOR
// If acceleration is equal to 1
#if (ACCELERATION != 1)
    accelDistance_1 =
        ((impStart - impValue) / acceleration) * ACCELERATION_FACTOR;
#else
    accelDistance_1 = abs((impStart - impValue) * ACCELERATION_FACTOR);
#endif
// End if acceleration is not equal 1
#else
    accelDistance_1 = ((impStart - impValue) / acceleration);
#endif

    if ((*dX) < (accelDistance_1 * 2)) {
      accelDistance_1 = (*dX) / 2;
    }
    accelDistance_2 = abs(*dX - accelDistance_1);

#ifdef _DEBUG
    sendData("dx >= dy");
    jumpLine();
    sendData(&accelDistance_1);
    jumpLine();
    sendData(&accelDistance_2);
    jumpLine();
    sendData("acceleration:  ");
    sendData(&acceleration);
    jumpLine();
#endif
  } else if ((*dY) > (*dX) && (*dY) != 0) {

#ifdef _ACCELERATION_REDUCTOR
#if (ACCELERATION != 1)
    accelDistance_1 =
        ((impStart - impValue) / acceleration) * ACCELERATION_FACTOR;
#else
    accelDistance_1 = abs((impStart - impValue) * ACCELERATION_FACTOR);
#endif
#else
    accelDistance_1 = ((impStart - impValue) / acceleration);
#endif

    if ((*dY) < (accelDistance_1 * 2)) {
      accelDistance_1 = (*dY) / 2;
    }
    accelDistance_2 = abs(*dY - accelDistance_1);

#ifdef _DEBUG
    sendData("dy > dx");
    jumpLine();
    sendData("acceleration:  ");
    sendData(&acceleration);
    jumpLine();
#endif
  }

  if ((*dZ) != 0) {

    if ((*dZ) > 0) {
      FLAG_dz_state = 1;
    } else {
      (*dZ) = -(*dZ);
      FLAG_dz_state = 2;
    }

#ifdef _ACCELERATION_REDUCTOR_Z
// If acceleration is equal to 1
#if (ACCELERATION_Z != 1)
    accelDistance_1_dz =
        ((jerk_dz - velocity_dz) / acceleration_dz) * ACCELERATION_FACTOR;
#else
    accelDistance_1_dz = abs((jerk_dz - velocity_dz) * ACCELERATION_FACTOR);
#endif
// End if acceleration is not equal 1
#else
    accelDistance_1_dz = ((jerk_z - velocity_z) / acceleration_dz);
#endif

    if ((*dZ) < (accelDistance_1_dz * 2)) {
      accelDistance_1_dz = (*dZ) / 2;
    }
    accelDistance_2_dz = abs(*dZ - accelDistance_1_dz);

#ifdef _DEBUG
    sendData("dz");
    jumpLine();
    sendData(&accelDistance_1_dz);
    jumpLine();
    sendData(&accelDistance_2_dz);
    jumpLine();
    sendData("acceleration_dz:  ");
    sendData(&acceleration_dz);
    jumpLine();
#endif

  }
}
/************************************************/