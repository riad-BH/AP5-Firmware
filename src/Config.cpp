#include "Config.h"


/********************************************************************/
void sendStartingScreen()
{
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
#if _PROTEUS == 1
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
  sendLine("AP5");
  jumpLine();
  sendLine("Firmware: ");
  sendLine(__DATE__);
  jumpLine();
#ifdef _DEBUG
  sendLine("DEBUGING MODE");
  jumpLine();
#endif
#if _PROTEUS == 1
  sendLine("PROTEUS MODE");
  jumpLine();
#endif
#ifdef _LIMITSWITCH
  sendLine("Limit switch: Activated");
  jumpLine();
#endif
#ifdef _POSITIONS
  sendLine("POSITIONS MODE");
  jumpLine();
#endif
  sendLine("Baud rate: ");
  sendData(USART_BAUD_RATE);
  jumpLine();
  sendLine("Speed: ");
  sendData(IMP_VALUE);
  jumpLine();
  sendLine("Acceleration: ");
  sendData(ACCELERATION);
  jumpLine();
  sendLine("Jerk: ");
  sendData(IMP_START);
  jumpLine();
  sendLine("Extruder's Speed: ");
  sendData(EXTRUDER_SPEED);
  jumpLine();
  sendLine("Manual Control Step: ");
  sendData(MANUAL_CONTROL_STEP);
  jumpLine();

  sendLine("$X");
  sendData(STEP_PER_MILLIMETER_X);
  sendLine(" Y");
  sendData(STEP_PER_MILLIMETER_Y);
  sendLine(" Z");
  sendData(STEP_PER_MILLIMETER_Z);
  sendLine(" J");
  sendData(IMP_START);
  sendLine(" A");
  sendData(ACCELERATION);
  sendLine(" I");
  sendData(IMP_VALUE);
  sendLine(" M");
  sendData(MANUAL_CONTROL_STEP);
  sendLine(" E");
  sendData(EXTRUDER_SPEED);
  sendLine(" B");
#ifdef _BLUETOOTH
  sendData(1);
#else
  sendData(0);
#endif
  sendLine(" L");
#ifdef _LIMITSWITCH
  sendData(1);
#else
  sendData(0);
  jumpLine();
#endif
}

void setIO()
{
  // X axis motors
  // B_OUTPUT(PIN_X_DIR);
  // B_OUTPUT(PIN_X_STEP);
    // // Y axis motors
  // B_OUTPUT(PIN_Y_DIR);
  // B_OUTPUT(PIN_Y_STEP);

  // // E axis motors
  // L_OUTPUT(PIN_E_DIR);
  // L_OUTPUT(PIN_E_STEP);

  // // Z1 and Z2 axis motors
  // L_OUTPUT(PIN_Z1_STEP);
  // L_OUTPUT(PIN_Z2_STEP);
  // L_OUTPUT(PIN_Z1_DIR);
  // L_OUTPUT(PIN_Z2_DIR);

  // // Hotend Pin
  // H_OUTPUT(PIN_HOTEND);

  // // Auto leveling sensor Pin
  // C_INPUT_PULLUP(PIN_AUTOLEVELING_SENSOR);

  // // Y axis Limit switch
  // D_INPUT_PULLUP(PIN_LIMITSWITCH_Y_FOWARD);
  // D_INPUT_PULLUP(PIN_LIMITSWITCH_Y_BACKWARD);

  // // X axis Limit switch
  // E_INPUT_PULLUP(PIN_LIMITSWITCH_X_FOWARD);
  // E_INPUT_PULLUP(PIN_LIMITSWITCH_X_BACKWARD);

  IOPort<IOPIN_X_STEP>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_X_DIR>::IOConfiguration(MODE_OUTPUT);

  IOPort<IOPIN_Y_STEP>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_Y_DIR>::IOConfiguration(MODE_OUTPUT);
  
  IOPort<IOPIN_Z1_STEP>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_Z1_DIR>::IOConfiguration(MODE_OUTPUT);
  
  IOPort<IOPIN_Z2_STEP>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_Z2_DIR>::IOConfiguration(MODE_OUTPUT);

  IOPort<IOPIN_E_STEP>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_E_DIR>::IOConfiguration(MODE_OUTPUT);

  IOPort<IOPIN_HOTEND>::IOConfiguration(MODE_OUTPUT);

  IOPort<IOPIN_AUTOLEVELING_SENSOR>::IOConfiguration(MODE_INPUT);

  IOPort<IOPIN_LIMITSWITCH_X_FOWARD>::IOConfiguration(MODE_INPUT_PULLUP);
  IOPort<IOPIN_LIMITSWITCH_Y_FOWARD>::IOConfiguration(MODE_INPUT_PULLUP);
  IOPort<IOPIN_LIMITSWITCH_X_BACKWARD>::IOConfiguration(MODE_INPUT_PULLUP);
  IOPort<IOPIN_LIMITSWITCH_Y_BACKWARD>::IOConfiguration(MODE_INPUT_PULLUP);

  IOPort<IOPIN_LCD_RS>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_E>::IOConfiguration(MODE_OUTPUT);

  IOPort<IOPIN_LCD_D0>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D1>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D2>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D3>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D4>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D5>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D6>::IOConfiguration(MODE_OUTPUT);
  IOPort<IOPIN_LCD_D7>::IOConfiguration(MODE_OUTPUT);



}
/********************************************************************/