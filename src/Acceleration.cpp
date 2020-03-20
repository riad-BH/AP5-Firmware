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
extern uint16_t impFinish;
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
static uint16_t future_impStart = IMP_START;
static uint16_t deccelDistance = 0;

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

 /* if (FLAG_G0_or_G1) {
    impValue = impControlableValue;
  } else {
    impValue = IMP_VALUE_G0;
  }*/

  impValue = impControlableValue;

  if (*dY < 0) {
    *dY = -(*dY);
    FLAG_dy_is_negative = 1;
  }

  if (*dX < 0) {
    *dX = -(*dX);
    FLAG_dx_is_negative = 1;
  }

  impStart = future_impStart;

  int32_t imp = static_cast<int32_t>(impFinish) *
                    ((static_cast<int32_t>(impValue) - IMP_START) / 180.0f) +
                IMP_START;
  impFinish = static_cast<uint16_t>(imp);

 /* sendData(&impFinish);
  jumpLine();*/

  if ((*dX) >= (*dY) && (*dX) != 0) {

#ifdef _ACCELERATION_REDUCTOR
// If acceleration is equal to 1
#if (ACCELERATION != 1)
    accelDistance_1 =
        ((impStart - impValue) / acceleration) * ACCELERATION_FACTOR;
#else
    if (impStart >= impValue) {
      accelDistance_1 = (impStart - impValue) * ACCELERATION_FACTOR;
    } else {
      accelDistance_1 = 0;
    }
    if (impFinish >= impValue) {
      deccelDistance = (impFinish - impValue) * ACCELERATION_FACTOR;
      accelDistance_2 = abs(*dX - deccelDistance);
    } else {
      deccelDistance = 0;
      accelDistance_2 = *dX;
    }

//  sendData(&accelDistance_2);
//  jumpLine();
#endif
// End if acceleration is not equal 1
#else
    accelDistance_1 = ((impStart - impValue) / acceleration);
#endif

    // Checking if we have enough distance to accelerate then decelerate
    if ((*dX) < (accelDistance_1 + deccelDistance)) {
      // Checking if it's an acceleration or deceleration
      if (impFinish < impStart) {
        // It's an acceleration
        accelDistance_1 = impStart - impFinish;
        // There is no deceleration
        accelDistance_2 = *dX;
        // Checking if we can accelerate till the impFinish
        if ((*dX) < accelDistance_1) {
          // No we can't so we need to calculate what speed we will be at
          accelDistance_1 = *dX;
          future_impStart = impStart - *dX;
        } else {
          // Yes we can
          future_impStart = impFinish;
          impValue = impFinish; // Here dodgy
        }
      } else {
        // It's a decceleration
        deccelDistance = impFinish - impStart;
        // There is no acceleration
        accelDistance_1 = 0;
        // Checking if we can decelerate till the impFinish
        if ((*dX) < deccelDistance) {          
          // No we can't so we need to calculate what speed we will be at
          accelDistance_2 = 0;
          future_impStart = impStart + *dX;
        } else {         
          // Yes we can
          accelDistance_2 = *dX - deccelDistance;
          impValue = impFinish; // Here dodgy
          future_impStart = impFinish;
        }
      }
      /* accelDistance_1 = (*dX) / 2;
       accelDistance_2 = abs(*dX - accelDistance_1);
       future_impStart = impStart;*/
    } else {
      future_impStart = impFinish;
    }
/*  accelDistance_2 = abs(*dX - accelDistance_1);*/

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
    /*accelDistance_1 =
        abs(static_cast<int16_t>(impStart - impValue) * ACCELERATION_FACTOR);
    uint16_t deccelDistance = abs((impFinish - impValue) * ACCELERATION_FACTOR);
    accelDistance_2 = abs(*dY - deccelDistance);*/

        if (impStart >= impValue) {
      accelDistance_1 = (impStart - impValue) * ACCELERATION_FACTOR;
    } else {
      accelDistance_1 = 0;
    }
    if (impFinish >= impValue) {
      deccelDistance = (impFinish - impValue) * ACCELERATION_FACTOR;
      accelDistance_2 = abs(*dY - deccelDistance);
    } else {
      deccelDistance = 0;
      accelDistance_2 = *dY;
    }
#endif
#else
    accelDistance_1 = ((impStart - impValue) / acceleration);
#endif

    /*   if ((*dY) < (accelDistance_1 + deccelDistance)) {
         accelDistance_1 = (*dY) / 2;
         accelDistance_2 = abs(*dY - accelDistance_1);
         future_impStart = impStart;
       }else{
         future_impStart = impFinish ;
       }
     //  accelDistance_2 = abs(*dY - accelDistance_1);*/

    if ((*dY) < (accelDistance_1 + deccelDistance)) {
      if (impFinish <= impStart) {
        accelDistance_1 = impStart - impFinish;
        accelDistance_2 = *dY;
        if ((*dY) < accelDistance_1) {
          accelDistance_1 = *dY;
          future_impStart = impStart - *dY;
        } else {
          future_impStart = impFinish;
          impValue = impFinish; // Here dodgy
        }
      } else {
        deccelDistance = impFinish - impStart;
        accelDistance_1 = 0;
        if ((*dY) < deccelDistance) {
          accelDistance_2 = 0;
          future_impStart = impStart + *dY;
        } else {
          accelDistance_2 = *dY - deccelDistance;
          impValue = impFinish; // here dodgy
          future_impStart = impFinish;
        }
      }
      /* accelDistance_1 = (*dY) / 2;
       accelDistance_2 = abs(*dY - accelDistance_1);
       future_impStart = impStart;*/
    } else {
      future_impStart = impFinish;
    }

#ifdef _DEBUG
    sendData("dy > dx");
    jumpLine();
    sendData("acceleration:  ");
    sendData(&acceleration);
    jumpLine();
#endif
  }

 /* sendData(&accelDistance_1);
  jumpLine();
  sendData(&accelDistance_2);
  jumpLine();
  sendData(&future_impStart);
  jumpLine();*/

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