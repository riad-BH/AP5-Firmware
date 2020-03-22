#include "Config.h"

/********************************************************************/
void sendStartingScreen(){
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
}

void setIO(){
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

  // Hotend Pin
  H_OUTPUT(PIN_HOTEND);

  // Y axis Limit switch
  D_INPUT_PULLUP(PIN_LIMITSWITCH_Y_FOWARD);
  D_INPUT_PULLUP(PIN_LIMITSWITCH_Y_BACKWARD);

  // X axis Limit switch
  E_INPUT_PULLUP(PIN_LIMITSWITCH_X_FOWARD);
  E_INPUT_PULLUP(PIN_LIMITSWITCH_X_BACKWARD);
}
/********************************************************************/