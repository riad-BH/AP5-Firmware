#ifndef H_MOTORS
#define H_MOTORS

#include "ArduinoInclude.h"
#include "ConstDefines.h"
#include "Extruder.h"
#include "Pins.h"
#include "Setting.h"
#include "Sending.h"
#include "TimerSetting.h"
/*
  * SETTING FUNCTION : SETS UP SOME SETTING FOR THE MOVE FUNCTION
*/
void fSettingUp();

void fSettingUpZ();

void fSettingUpE();

/*
  * MOVE FUNCTION : ACTIONS THE MOTORS
*/
void fMoveXYE();

void fMoveZ();

void fMoveE();

#endif // H_MOTORS
