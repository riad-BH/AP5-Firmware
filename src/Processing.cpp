#include "Processing.h"

/************************************************/
// Impulsion size at the start in microseconds
uint16_t impStart = IMP_START;
// Impulsion size in microseconds
uint16_t impValue = IMP_VALUE;
// Implusion size at the end in microseconds
uint16_t impFinish = 180;
// Controlable impulsion size in microseconds
uint16_t impControlableValue = IMP_VALUE;
// Impulsion size at the start in microseconds for Z axis
uint16_t jerk_z = JERK_Z;
// Impulsion size in microseconds for Z axis
uint16_t velocity_z = VELOCITY_Z;
/************************************************/
// Extruder speed
uint8_t extruderSpeed = EXTRUDER_SPEED;
// Flag Extruder if there is extrusion or not
uint8_t FLAG_extruder = 0;
// Flag set on if there is an extrusion
uint8_t FLAG_extrusion_for_timer = 0;
/************************************************/
// Flag is set to 1 if bluetooth is activated
uint8_t FLAG_bluetoothState = 0;
/************************************************/
// Flag is set to 1 if limit switch is activated
uint8_t FLAG_limitSwitchState = 0;
/************************************************/
// Flag is set to 1 if it's a G1 command
// Or if it's G0 command it is set to 0
uint8_t FLAG_G0_or_G1 = 0;
/************************************************/
// Extruding value
int32_t de = 0;
/************************************************/

/*************** Local Variables ***************/
// X axis limits
static int16_t minX = MIN_X;
static int16_t maxX = MAX_X;
// Y axis limits
static int16_t minY = MIN_Y;
static int16_t maxY = MAX_Y;
// Z axis limits
static int16_t minZ = MIN_Z;
static int16_t maxZ = MAX_Z;
/************************************************/
// Manual control step
static uint8_t mcs = MANUAL_CONTROL_STEP;
/************************************************/
static uint8_t FLAG_fanState = 0;
/************************************************/
#ifndef _ABSOLUTE_POSITIONS
// X new position
static float newX = 0.0;
// Y new position
static float newY = 0.0;
// Z new position
static float newZ = 0.0;
// X old position
static float oldX = 0.0;
// Y old position
static float oldY = 0.0;
// Z old position
static float oldZ = 0.0;
#endif
/************************************************/

/*************** Extern Variables ***************/
extern uint8_t acceleration;
/************************************************/
extern uint16_t spmX;
extern uint16_t spmY;
extern uint16_t spmZ;
/************************************************/

/*************** Extern Functions ***************/
// Function to send data
extern void sendData(String);
extern void sendData(float *);
extern void sendData(uint8_t *);
extern void sendData(int8_t *);
extern void sendData(uint16_t *);
extern void sendData(int16_t *);
extern void sendData(uint32_t *);
extern void sendData(int32_t *);
/************************************************/
// Function for starting the USART
extern void setUSART0(const uint32_t);
extern void setUSART1(const uint16_t);
extern void unsetUSART1();
/************************************************/
//  Setting INT0/1/2/3/4/5 for falling edge
extern void setInt(uint8_t);
//  Desactivating interrupt
extern void unsetInt(uint8_t);
/************************************************/
// Function for Setting up the extruder for mouvement
extern void fSettingUpE();
/************************************************/

/************************************************/
// Jump line function
#ifdef _PROTEUS
#define jumpLine() sendData("\r")
#else
#define jumpLine() sendData("\n")
#endif
/************************************************/

uint8_t fProcessing(char *dataLine, char _localBuffer[8], int32_t *dX,
                    int32_t *dY, int32_t *dZ) {
  // Index for the processing function
  uint8_t actualIndex = 0;

  switch (dataLine[actualIndex++]) {

  case 'G': {
    // Store the second chacarcter then increment the actual index
    _localBuffer[0] = dataLine[actualIndex++];
    // Close the array
    _localBuffer[1] = '\0';

    // Transform the second character from Ascii to an int then read it
    switch (atoi(_localBuffer)) {

    // G0 function
    case 0: {
      FLAG_G0_or_G1 = 0;
      uint8_t indexChar = 0;
      // Search the character X begining from the second character
      while (dataLine[indexChar] != '\0') {
        switch (dataLine[indexChar]) {

        // Case X
        case 'X': {
          char *indexX = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dX = round(atof(indexX + 1) * spmX);
#else
          newX = (int32_t)(atof(indexX + 1) * spmX);
          *dX = (newX - oldX);
          oldX = newX;
#endif
#else
          *dX = atol(indexX + 1);
#endif
          break;
        }

        // Case Y
        case 'Y': {
          char *indexY = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dY = round(atof(indexY + 1) * spmY);
#else
          newY = (int32_t)(atof(indexY + 1) * spmY);
          *dY = (newY - oldY);
          oldY = newY;
#endif
#else
          *dY = atol(indexY + 1);
#endif
          break;
        }

        // Case Z
        case 'Z': {
          char *indexZ = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dZ = round(atof(indexZ + 1) * spmZ);
#else
          newZ = (int16_t)(atof(indexZ + 1) * spmZ);
          *dZ = (newZ - oldZ);
          oldZ = newZ;
#endif
#else
          *dZ = atol(indexZ + 1);
#endif
          break;
        }

        // Printer speed
        case 'F': {
          char *indexF = &dataLine[indexChar];
          impControlableValue = atoi(indexF + 1);
          break;
        }

        // Impulsion finish
        case 'J': {
          char *indexJ = strchr(dataLine, 'J');
          impFinish = atoi(indexJ + 1);
          break;
        }

        default:
          break;
        }
        indexChar++;
      }

      FLAG_extruder = false;
      return 0;
      break;
    } // END CASE G0

    // G1 function
    case 1: {
      FLAG_G0_or_G1 = 1;
      // Search the character X begining from the second character
      uint8_t indexChar = 2;

      // Reset extruder's flag
      FLAG_extruder = false;
      while (dataLine[indexChar] != '\0') {
        switch (dataLine[indexChar]) {

        // Case X
        case 'X': {
          char *indexX = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dX = round(atof(indexX + 1) * spmX);
#else
          newX = (int32_t)(atof(indexX + 1) * spmX);
          *dX = (newX - oldX);
          oldX = newX;
#endif
#else
          *dX = atol(indexX + 1);
#endif
          break;
        }

        // Case Y
        case 'Y': {
          char *indexY = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dY = round(atof(indexY + 1) * spmY);
#else
          newY = (int32_t)(atof(indexY + 1) * spmY);
          *dY = (newY - oldY);
          oldY = newY;
#endif
#else
          *dY = atol(indexY + 1);
#endif
          break;
        }

        // Case Z
        case 'Z': {
          char *indexZ = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dZ = round(atof(indexZ + 1) * spmZ);
#else
          newZ = (int16_t)(atof(indexZ + 1) * spmZ);
          *dZ = (newZ - oldZ);
          oldZ = newZ;
#endif
#else
          *dZ = atol(indexZ + 1);
#endif
          break;
        }

        // Case E
        case 'E': {
          FLAG_extruder = true;
#ifdef _GET_EXTRUDER_SPEED
          char *indexE = &dataLine[indexChar];
          extruderSpeed = atoi(indexE + 1);
#ifdef _DEBUG
          sendData(&extruderSpeed);
          jumpLine();
#endif
#endif
          break;
        }

        case 'F': {
          char *indexF = &dataLine[indexChar];
          impControlableValue = atoi(indexF + 1);
          break;
        }

        // Impulsion finish
        case 'J': {
          char *indexJ = strchr(dataLine, 'J');
          impFinish = atoi(indexJ + 1);
          break;
        }

        /*// Retract
        case 'R': {
          de = 1800;
          FLAG_extrusion_for_timer = 1;
          break;
        }
        // Rextrude
        case 'H': {
          de = 1800;
          FLAG_extrusion_for_timer = 2;
          break;
        }*/

        default:
          break;
        }

        indexChar++;
      }

      return 0;
      break;
    } // END CASE G1

    // DEFAULT G case
    default: {
      sendData("G ERROR");
      jumpLine();
      return 1;
      break;
    }
    } // END CASE G
    break;
  } // END G COMMAND

  case '$': {
    switch (dataLine[actualIndex++]) {

    // Manual control's step
    case 'M': {
      char *indexC = strchr(dataLine, 'C');
      mcs = atoi(indexC + 1);
      sendData("Manual control's step:  ");
      sendData(&mcs);
      jumpLine();
      return 1;
      break;
    }

    // Bluetooth
    case 'B': {
      FLAG_bluetoothState = !FLAG_bluetoothState;
      sendData("Bluetooth is:  ");
      sendData(&FLAG_bluetoothState);
      jumpLine();
      if (FLAG_bluetoothState) {
        setUSART1(BLUETOOTH_BAUD_RATE);
      } else {
        unsetUSART1();
      }
      return 1;
      break;
    }

    // Limit switch
    case 'L': {
      FLAG_limitSwitchState = !FLAG_limitSwitchState;
      sendData("Limit switch is:  ");
      sendData(&FLAG_limitSwitchState);
      jumpLine();
      if (FLAG_limitSwitchState) {
        setInt(0);
        setInt(1);
        setInt(4);
        setInt(5);
      } else {
        unsetInt(0);
        unsetInt(1);
        unsetInt(4);
        unsetInt(5);
      }
      return 1;
      break;
    }

    // Manual control
    case '+': {
      if (dataLine[actualIndex] == 'X') {
        *dX = mcs * spmX;
        *dY = 0;
        *dZ = 0;
      } else if (dataLine[actualIndex] == 'Y') {
        *dX = 0;
        *dY = mcs * spmY;
        *dZ = 0;
      } else if (dataLine[actualIndex] == 'Z') {
        *dX = 0;
        *dY = 0;
        *dZ = mcs * spmZ;
      }
      impFinish = 180;
      FLAG_G0_or_G1 = 0;
      impValue = IMP_VALUE_G0;
      return 0;
      break;
    }

    // Manual control
    case '-': {
      if (dataLine[actualIndex] == 'X') {
        *dX = -(int32_t)(mcs * spmX);
        *dY = 0;
        *dZ = 0;
      } else if (dataLine[actualIndex] == 'Y') {
        *dX = 0;
        *dY = -(int32_t)(mcs * spmY);
        *dZ = 0;

      } else if (dataLine[actualIndex] == 'Z') {
        *dX = 0;
        *dY = 0;
        *dZ = -(int16_t)(mcs * spmZ);
      }
      impFinish = 180;
      FLAG_G0_or_G1 = 0;
      impValue = IMP_VALUE_G0;
      return 0;
      break;
    }

    // Jerk impulsion
    case 'J': {
      char *indexJ = strchr(dataLine, 'J');
      impStart = atoi(indexJ + 1);
      sendData("Starting impulsion's size:  ");
      sendData(&impStart);
      jumpLine();
      return 1;
      break;
    }

    // Working impulsion
    case 'I': {
      char *indexI = strchr(dataLine, 'I');
      impControlableValue = atoi(indexI + 1);
      sendData("Working impulsion's size:  ");
      sendData(&impControlableValue);
      jumpLine();
      return 1;
      break;
    }

    // Extruder speed
    case 'E': {
      char *indexE = strchr(dataLine, 'E');
      extruderSpeed = atoi(indexE + 1);
      sendData("Extrusion speed:  ");
      sendData(&extruderSpeed);
      jumpLine();
      return 1;
      break;
    }

    // Extrude
    case 'e': {
      char *index_e = strchr(dataLine, 'e');
#ifdef _ABSOLUTE_EXTRUSION
      de = atol(index_e + 1);
#else
      de = atol(index_e + 1) * EXTRUDER_GEAR_COEFFICIENT;
#endif
      FLAG_extrusion_for_timer = 1;
      if (de >= 0) {
        PORTA &= ~(_BV(PIN_E_DIR));
      } else {
        PORTA |= (_BV(PIN_E_DIR));
        de = -(de);
      }
      fSettingUpE();
      return 1;
      break;
    }

    // Acceleration
    case 'A': {
      char *indexA = strchr(dataLine, 'A');
      acceleration = atoi(indexA + 1);
      sendData("Acceleration:  ");
      sendData(&acceleration);
      jumpLine();
      return 1;
      break;
    }

    // Fan
    case 'f': {
      FLAG_fanState = !FLAG_fanState;
      sendData("Fan is : ");
      if (FLAG_fanState) {
        sendData("ON");
      } else {
        sendData("OFF");
      }
      jumpLine();
      return 1;
      break;
    }

    // X Step per milimeter
    case 'X': {
      char *indexS = strchr(dataLine, 'X');
      spmX = atoi(indexS + 1);
      sendData("X Step per milimeter:  ");
      sendData(&spmX);
      jumpLine();
      return 1;
      break;
    }

    // Y Step per milimeter
    case 'Y': {
      char *indexS = strchr(dataLine, 'Y');
      spmY = atoi(indexS + 1);
      sendData("Y Step per milimeter:  ");
      sendData(&spmY);
      jumpLine();
      return 1;
      break;
    }

    // Z Step per milimeter
    case 'Z': {
      char *indexS = strchr(dataLine, 'Z');
      spmZ = atoi(indexS + 1);
      sendData("Z Step per milimeter:  ");
      sendData(&spmZ);
      jumpLine();
      return 1;
      break;
    }

#ifndef _ABSOLUTE_POSITIONS
    // Reset Origin
    case 'O': {
      oldX = 0.0;
      oldY = 0.0;
      oldZ = 0.0;
      sendData("Resetting the new origin");
      jumpLine();
      return 1;
      break;
    }
#endif

    default: {
      sendData("$ Error");
      jumpLine();
      return 1;
      break;
    }
    }
    break;
  } // END $ COMMAND

  // DEFAULT COMMAND
  default: {
    sendData("Unknown command:  ");
    sendData(dataLine);
    return 1;
    break;
  }

  } // END SWITCH COMMAND

  return 1;
} // END FUNCTION
/************************************************/

void fSetLimits(float *x1, float *y1, float *z1) {
  // Resizing the points to fit the limits
  if (*x1 >= maxX) {
    *x1 = maxX;
  } else if (*x1 <= minX) {
    *x1 = minX;
  }

  if (*y1 >= maxY) {
    *y1 = maxY;
  } else if (*y1 <= minY) {
    *y1 = minY;
  }

  if (*z1 >= maxZ) {
    *z1 = maxZ;
  } else if (*z1 <= minZ) {
    *z1 = minZ;
  }
}
/************************************************/