
/*================================================================
    INCLUDES AND DEFINES
 =================================================================*/

#include "IncludeFiles.h"

#define sendXYZ()                                                              \
  sendData(&dx);                                                               \
  jumpLine();                                                                  \
  sendData(&dy);                                                               \
  jumpLine();                                                                  \
  sendData(&dz);                                                               \
  jumpLine()
/*================================================================*/

/*================================================================
    MAIN PROGRAM
 =================================================================*/

int main() {
  cli();

  // X axis motors
  B_OUTPUT(PIN_X_DIR);
  B_OUTPUT(PIN_X_STEP);

  // Y axis motors
  B_OUTPUT(PIN_Y_DIR);
  B_OUTPUT(PIN_Y_STEP);

  // E axis motors
  A_OUTPUT(PIN_E_DIR);
  A_OUTPUT(PIN_E_STEP);

  // Z1 and Z2 axis motors
  L_OUTPUT(PIN_Z1_STEP);
  L_OUTPUT(PIN_Z2_STEP);
  L_OUTPUT(PIN_Z1_DIR);
  L_OUTPUT(PIN_Z2_DIR);

  // Y axis Limit switch
  D_INPUT_PULLUP(PIN_LIMITSWITCH_Y_FOWARD);
  D_INPUT_PULLUP(PIN_LIMITSWITCH_Y_BACKWARD);

  // X axis Limit switch
  E_INPUT_PULLUP(PIN_LIMITSWITCH_X_FOWARD);
  E_INPUT_PULLUP(PIN_LIMITSWITCH_X_BACKWARD);

  setUSART0(USART_BAUD_RATE);

#ifdef _BLUETOOTH
  setUSART1(BLUETOOTH_BAUD_RATE);
  FLAG_bluetoothState = 1;
#endif

#ifdef _LIMITSWITCH

  setInt(0);
  setInt(1);
  setInt(4);
  setInt(5);
  FLAG_limitSwitchState = 1;
#endif

  sei();

#ifdef _BLUETOOTH
  sendData1("AP5");
  jumpLine();
  sendData1("Bluetooth: Activated");
  jumpLine();
#ifdef _DEBUG
  sendData1("DEBUGING MODE");
  jumpLine();
#endif
#ifdef _PROTEUS
  sendData1("PROTEUS MODE");
  jumpLine();
#endif
#ifdef _LIMITSWITCH
  sendData1("Limit switch: Activated");
  jumpLine();
#endif
#ifdef _POSITIONS
  sendData1("POSITIONS MODE");
  jumpLine();
#endif
  sendData1("Baud rate: ");
  sendData1(BLUETOOTH_BAUD_RATE);
  jumpLine();
  sendData1("Speed: ");
  sendData1(IMP_VALUE);
  jumpLine();
  sendData1("Acceleration: ");
  sendData1(ACCELERATION);
  jumpLine();
  sendData1("Jerk: ");
  sendData1(IMP_START);
  jumpLine();
  sendData1("Extruder's Speed: ");
  sendData1(EXTRUDER_SPEED);
  jumpLine();
  sendData1("Manual Control Step: ");
  sendData1(MANUAL_CONTROL_STEP);
  jumpLine();
#endif
  sendData("AP5");
  jumpLine();
  sendData("Firmware: ");
  sendData(__DATE__);
  jumpLine();
#ifdef _DEBUG
  sendData("DEBUGING MODE");
  jumpLine();
#endif
#ifdef _PROTEUS
  sendData("PROTEUS MODE");
  jumpLine();
#endif
#ifdef _LIMITSWITCH
  sendData("Limit switch: Activated");
  jumpLine();
#endif
#ifdef _POSITIONS
  sendData("POSITIONS MODE");
  jumpLine();
#endif
  sendData("Baud rate: ");
  sendData(USART_BAUD_RATE);
  jumpLine();
  sendData("Speed: ");
  sendData(IMP_VALUE);
  jumpLine();
  sendData("Acceleration: ");
  sendData(ACCELERATION);
  jumpLine();
  sendData("Jerk: ");
  sendData(IMP_START);
  jumpLine();
  sendData("Extruder's Speed: ");
  sendData(EXTRUDER_SPEED);
  jumpLine();
  sendData("Manual Control Step: ");
  sendData(MANUAL_CONTROL_STEP);
  jumpLine();

  sendData("$X");
  sendData(STEP_PER_MILLIMETER_X);
  sendData(" Y");
  sendData(STEP_PER_MILLIMETER_Y);
  sendData(" Z");
  sendData(STEP_PER_MILLIMETER_Z);
  sendData(" J");
  sendData(IMP_START);
  sendData(" A");
  sendData(ACCELERATION);
  sendData(" I");
  sendData(IMP_VALUE);
  sendData(" M");
  sendData(MANUAL_CONTROL_STEP);
  sendData(" E");
  sendData(EXTRUDER_SPEED);
  sendData(" B");
#ifdef _BLUETOOTH
  sendData(1);
#else
  sendData(0);
#endif
  sendData(" L");
#ifdef _LIMITSWITCH
  sendData(1);
#else
  sendData(0);
  jumpLine();

#endif

  while (1) {
    switch (FLAG_machine) {

    /* RECEIVING */
    case 0:
      if (FLAG_RX) {
        RX_stringPointer = RX_volatilePointer;
        RX_volatilePointer = 0;
        FLAG_machine = PROCESSING; // Next step activated
        FLAG_RX = 0;
      }
      break;

    /* PROCESSING */
    case 1:
   // PORTL |= _BV(PIN_Z_STEP);
      if (FLAG_RX_array1_state == FULL) {
        if (!fProcessing(RX_array1, localBuffer, &dx, &dy, &dz)) {
          FLAG_RX_array1_state = PROCESSED;
#ifdef _DEBUG
          sendXYZ();
#endif
          FLAG_array1_or_array2 = ARRAY_1;
#ifdef _DEBUG
          sendData("Array 1");
          jumpLine();
#endif
          fAccelCompute(&dx, &dy,&dz);
          FLAG_machine = ACTION; // Next step activated
        } else {
          FLAG_RX_array1_state = EMPTY;
          FLAG_machine = RECEIVING;
        }
      } else if (FLAG_RX_array2_state == FULL) {
        if (!fProcessing(RX_array2, localBuffer, &dx, &dy, &dz)) {
          FLAG_RX_array2_state = PROCESSED;
#ifdef _DEBUG
          sendXYZ();
#endif
          FLAG_array1_or_array2 = ARRAY_2;
#ifdef _DEBUG
          sendData("Array 2");
          jumpLine();
#endif
          fAccelCompute(&dx, &dy,&dz);
          FLAG_machine = ACTION; // Next step activated
        } else {
          FLAG_RX_array2_state = EMPTY;
          FLAG_machine = RECEIVING;
        }
      } else {
        FLAG_machine = RECEIVING; // Go back to 0
      }
      
      break;

    /* SETTING UP AND ACTION */
    case 2:
      if (!FLAG_motorsActivated) {
        fSettingUp();
#ifdef _PROTEUS
        sendData(">\r");
#else
        sendData(">\n");
#endif
        FLAG_machine = RECEIVING; // Go back to 0
      }
      break;

    /*DEFAULT */
    default:
      sendData("State error");
      jumpLine();
      break;
    }
  }

  return 0;
}

/*================================================================*/

#include "ISR.h"
