#include "Processing.h"

/************************************************/
// Flag is set to 1 if bluetooth is activated
uint8_t FLAG_bluetoothState = 0;
/************************************************/
// Flag is set to 1 if limit switch is activated
uint8_t FLAG_limitSwitchState = 0;
/************************************************/
// Manual control step
static uint8_t mcs = MANUAL_CONTROL_STEP;
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

/************************************************/
// X axis steps per milimeter
uint16_t spmX = STEP_PER_MILLIMETER_X;
// Y axis steps per milimeter
uint16_t spmY = STEP_PER_MILLIMETER_Y;
// Z axis steps per milimeter
uint16_t spmZ = STEP_PER_MILLIMETER_Z;
/************************************************/

extern Motors steppers;
/************************************************/

#define mq_head mq.mouvements_array[mq.head]

uint8_t fProcessing(const char *dataLine, char _localBuffer[8], MouvementQueue &mq)
{

  // Index for the processing function
  uint8_t actualIndex = 0;
  mq.flushMouvemetBuffer();

  switch (dataLine[actualIndex++])
  {

  case 'G':
  {
    // Store the second chacarcter then increment the actual index
    _localBuffer[0] = dataLine[actualIndex++];
    // Close the array
    _localBuffer[1] = '\0';

    // Transform the second character from Ascii to an int then read it
    switch (atoi(_localBuffer))
    {

    // G0 function
    case 0:
    {
      mq.setDe_state(0);

      uint8_t indexChar = 2;

      // Search the character X begining from the second character
      while (dataLine[indexChar] != '\0')
      {
        switch (dataLine[indexChar])
        {

        // Case X
        case 'X':
        {
          const char *indexX = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dX = round(atof(indexX + 1) * spmX);
#else
          newX = (int32_t)(atof(indexX + 1) * spmX);
          *dX = (newX - oldX);
          oldX = newX;
#endif
#else
          mq.setDx(atol(indexX + 1));
#endif
          break;
        }

        // Case Y
        case 'Y':
        {
          const char *indexY = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dY = round(atof(indexY + 1) * spmY);
#else
          newY = (int32_t)(atof(indexY + 1) * spmY);
          *dY = (newY - oldY);
          oldY = newY;
#endif
#else
          mq.setDy(atol(indexY + 1));
#endif
          break;
        }

        // Case Z
        case 'Z':
        {
          const char *indexZ = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dZ = round(atof(indexZ + 1) * spmZ);
#else
          newZ = (int16_t)(atof(indexZ + 1) * spmZ);
          *dZ = (newZ - oldZ);
          oldZ = newZ;
#endif
#else
          mq.setDz(atol(indexZ + 1));
#endif
          break;
        }

        // Printer speed
        case 'F':
        {
          const char *indexF = &dataLine[indexChar];
          mq.setImp_value(atoi(indexF + 1));
          break;
        }

        // Impulsion finish
        case 'J':
        {
          const char *indexJ = strchr(dataLine, 'J');
          mq.setAngle(atoi(indexJ + 1));
          break;
        }

        default:
          break;
        }
        indexChar++;
      }

      return 0;
      break;
    } // END CASE G0

    // G1 function
    case 1:
    {

      mq.setDe_state(1);

      // Search the character X begining from the second character
      uint8_t indexChar = 2;

      while (dataLine[indexChar] != '\0')
      {
        switch (dataLine[indexChar])
        {

        // Case X
        case 'X':
        {
          const char *indexX = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dX = round(atof(indexX + 1) * spmX);
#else
          newX = (int32_t)(atof(indexX + 1) * spmX);
          *dX = (newX - oldX);
          oldX = newX;
#endif
#else
          mq.setDx(atol(indexX + 1));
#endif
          break;
        }

        // Case Y
        case 'Y':
        {
          const char *indexY = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dY = round(atof(indexY + 1) * spmY);
#else
          newY = (int32_t)(atof(indexY + 1) * spmY);
          *dY = (newY - oldY);
          oldY = newY;
#endif
#else
          mq.setDy(atol(indexY + 1));
#endif
          break;
        }

        // Case Z
        case 'Z':
        {
          const char *indexZ = &dataLine[indexChar];
#ifdef _STEP_PER_MILIMETER_CALCULATION
#ifdef _ABSOLUTE_POSITIONS
          *dZ = round(atof(indexZ + 1) * spmZ);
#else
          newZ = (int16_t)(atof(indexZ + 1) * spmZ);
          *dZ = (newZ - oldZ);
          oldZ = newZ;
#endif
#else
          mq.setDz(atol(indexZ + 1));
#endif
          break;
        }

        // Case E
        case 'E':
        {

#ifdef _GET_EXTRUDER_SPEED
          char *indexE = &dataLine[indexChar];
          extruderSpeed = atoi(indexE + 1);
#ifdef _DEBUG
          sendData(&extruderSpeed);
          jumpLine();
#endif
#endif

          const char *indexE = &dataLine[indexChar];
          mq.setDe(atol(indexE + 1) * EXTRUDER_GEAR_COEFFICIENT);
          //mq.setDe(atol(indexE + 1));
          break;
        }

        case 'F':
        {
          const char *indexF = &dataLine[indexChar];
          mq.setImp_value(atoi(indexF + 1));
          break;
        }

        // Impulsion finish
        case 'J':
        {
          char *indexJ = strchr(dataLine, 'J');
          mq.setAngle(atoi(indexJ + 1));
          break;
        }

        default:
          break;
        }

        indexChar++;
      }

      return 0;
      break;
    } // END CASE G1

    // DEFAULT G case
    default:
    {
      sendLine("G ERROR");
      jumpLine();
      return 1;
      break;
    }
    } // END CASE G
    break;
  } // END G COMMAND

  case '$':
  {
    switch (dataLine[actualIndex++])
    {

    // Manual control's step
    case 'M':
    {
      char *indexC = strchr(dataLine, 'C');
      mcs = atoi(indexC + 1);
      sendLine("Manual control's step:  ");
      sendData(mcs);
      jumpLine();
      return 1;
      break;
    }

    // Temperature control
    case 'T':
    {
      char *indexT = strchr(dataLine, 'T');
      uint16_t voltage = atoi(indexT + 1);
      TempControl::setTemperature(voltage);
      sendLine("Voltage temperature is set now to: ");
      sendData(voltage);
      jumpLine();
      return 1;
      break;
    }

    // Bluetooth
    case 'B':
    {
      FLAG_bluetoothState = !FLAG_bluetoothState;
      sendLine("Bluetooth is:  ");
      sendData(FLAG_bluetoothState);
      jumpLine();
      if (FLAG_bluetoothState)
      {
        setUSART1(BLUETOOTH_BAUD_RATE);
      }
      else
      {
        unsetUSART1();
      }
      return 1;
      break;
    }

    // Limit switch
    case 'L':
    {
      FLAG_limitSwitchState = !FLAG_limitSwitchState;
      sendLine("Limit switch is:  ");
      sendData(FLAG_limitSwitchState);
      jumpLine();
      if (FLAG_limitSwitchState)
      {
        setInt(0);
        setInt(1);
        setInt(4);
        setInt(5);
      }
      else
      {
        unsetInt(0);
        unsetInt(1);
        unsetInt(4);
        unsetInt(5);
      }
      return 1;
      break;
    }

    // Manual control
    case '+':
    {
      if (dataLine[actualIndex] == 'X')
      {
        mq.setDx(mcs * spmX);
        mq.setDy(0);
        mq.setDz(0);
      }
      else if (dataLine[actualIndex] == 'Y')
      {
        mq.setDx(0);
        mq.setDy(mcs * spmY);
        mq.setDz(0);
      }
      else if (dataLine[actualIndex] == 'Z')
      {
        mq.setDx(0);
        mq.setDy(0);
        mq.setDz(mcs * spmZ);
      }

      mq.setAngle(180);
      mq.setImp_value(IMP_VALUE_G0);
      return 0;
      break;
    }

    // Manual control
    case '-':
    {
      if (dataLine[actualIndex] == 'X')
      {
        mq.setDx(-(int32_t)(mcs * spmX));
        mq.setDy(0);
        mq.setDz(0);
      }
      else if (dataLine[actualIndex] == 'Y')
      {
        mq.setDx(0);
        mq.setDy(-(int32_t)(mcs * spmY));
        mq.setDz(0);
      }
      else if (dataLine[actualIndex] == 'Z')
      {
        mq.setDx(0);
        mq.setDy(0);
        mq.setDz(-(int32_t)(mcs * spmZ));
      }
      mq.setAngle(180);
      mq.setImp_value(IMP_VALUE_G0);
      return 0;
      break;
    }

    // Jerk impulsion
    case 'J':
    {
      char *indexJ = strchr(dataLine, 'J');
      mq.setAngle(atoi(indexJ + 1));
      sendLine("Next angle set to: something");
      return 1;
      break;
    }

    // Working impulsion
    case 'I':
    {
      char *indexI = strchr(dataLine, 'I');
      mq.setImp_value(atoi(indexI + 1));
      sendLine("Working impulsion's size: something");
      return 1;
      break;
    }

    // Extruder speed
    case 'E':
    {
      char *indexE = strchr(dataLine, 'E');
      mq.setExtruderSpeed(atoi(indexE + 1));
      sendLine("Extrusion speed: something");
      return 1;
      break;
    }

    // Acceleration
    case 'A':
    {
      char *indexA = strchr(dataLine, 'A');
      mq.setAcceleration(atoi(indexA + 1));
      sendLine("Acceleration:  ");
      sendData(mq.getAcceleration(mq.head));
      jumpLine();
      return 1;
      break;
    }

    // Fan
    case 'f':
    {
    }

    // X Step per milimeter
    case 'X':
    {
      char *indexS = strchr(dataLine, 'X');
      spmX = atoi(indexS + 1);
      sendLine("X Step per milimeter:  ");
      sendData(spmX);
      jumpLine();
      return 1;
      break;
    }

    // Y Step per milimeter
    case 'Y':
    {
      char *indexS = strchr(dataLine, 'Y');
      spmY = atoi(indexS + 1);
      sendLine("Y Step per milimeter:  ");
      sendData(spmY);
      jumpLine();
      return 1;
      break;
    }

    // Z Step per milimeter
    case 'Z':
    {
      char *indexS = strchr(dataLine, 'Z');
      spmZ = atoi(indexS + 1);
      sendLine("Z Step per milimeter:  ");
      sendData(spmZ);
      jumpLine();
      return 1;
      break;
    }

    // Bed leveling
    case 'b':
    {
      mq.setDx(0);
      mq.setDy(0);
      mq.setDz(-40000);
      Flags::setFlag_automatic_bed_leveling(1);
      return 0;
      break;
    }

#ifndef _ABSOLUTE_POSITIONS
    // Reset Origin
    case 'O':
    {
      oldX = 0.0;
      oldY = 0.0;
      oldZ = 0.0;
      sendData("Resetting the new origin");
      jumpLine();
      return 1;
      break;
    }
#endif

    default:
    {
      sendLine("$ Error");
      jumpLine();
      return 1;
      break;
    }
    }
    break;
  } // END $ COMMAND

  // DEFAULT COMMAND
  default:
  {
    sendLine("Unknown command:  ");
    sendLine(dataLine);
    return 1;
    break;
  }

  } // END SWITCH COMMAND

  return 1;
} // END FUNCTION
/************************************************/
