#ifndef H_PINS
#define H_PINS

#include "IOPins.h"

/*================================================================
    AXIS MOTORS PINS
 =================================================================*/

// X axis motors pins
#define PIN_X_STEP IOPIN_X_STEP.pin_number
#define PIN_X_DIR IOPIN_X_DIR.pin_number

// Y axis motors pins
#define PIN_Y_STEP IOPIN_Y_STEP.pin_number
#define PIN_Y_DIR IOPIN_Y_DIR.pin_number

// Z 1 axis motors pins
#define PIN_Z1_STEP IOPIN_Z1_STEP.pin_number
#define PIN_Z1_DIR IOPIN_Z1_DIR.pin_number

// Z 2 axis motors pins
#define PIN_Z2_STEP IOPIN_Z2_STEP.pin_number
#define PIN_Z2_DIR IOPIN_Z2_DIR.pin_number
/*================================================================*/

/*================================================================
    EXTRUDER
 =================================================================*/
// Extruders motors pins
#define PIN_E_STEP IOPIN_E_STEP.pin_number
#define PIN_E_DIR IOPIN_E_DIR.pin_number
/*================================================================*/

/*================================================================
    FAN
 =================================================================*/
#define PIN_FAN IOPIN_FAN.pin_number
/*================================================================*/

/*================================================================
    THERMORESISTOR and Hoten
 =================================================================*/
#define PIN_HOTEND IOPIN_HOTEND.pin_number
/*================================================================*/

/*================================================================
    THERMORESISTOR and Hoten
 =================================================================*/
#define PIN_AUTOLEVELING_SENSOR IOPIN_AUTOLEVELING_SENSOR.pin_number
/*================================================================*/

/*================================================================
    LIMIT SWITCHS
 =================================================================*/
#define PIN_LIMITSWITCH_X_FOWARD IOPIN_LIMITSWITCH_X_FOWARD.pin_number
#define PIN_LIMITSWITCH_X_BACKWARD IOPIN_LIMITSWITCH_X_BACKWARD.pin_number

#define PIN_LIMITSWITCH_Y_FOWARD IOPIN_LIMITSWITCH_Y_FOWARD.pin_number
#define PIN_LIMITSWITCH_Y_BACKWARD IOPIN_LIMITSWITCH_Y_BACKWARD.pin_number
/*================================================================*/

/*================================================================
    LCD
 =================================================================*/
#define PIN_LCD_RS IOPIN_LCD_RS.pin_number
#define PIN_LCD_E IOPIN_LCD_E.pin_number
#define PIN_LCD_D7 IOPIN_LCD_D7.pin_number
#define PIN_LCD_D6 IOPIN_LCD_D6.pin_number
#define PIN_LCD_D5 IOPIN_LCD_D5.pin_number
#define PIN_LCD_D4 IOPIN_LCD_D4.pin_number

#endif
