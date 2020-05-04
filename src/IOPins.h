#ifndef __IOPINS_H__
#define __IOPINS_H__

#include "IOFunctions.h"
/*================================================================
    AXIS MOTORS PINS
 =================================================================*/

// X axis motors pins
#define IOPIN_X_STEP D_PIN_53
#define IOPIN_X_DIR D_PIN_52

// Y axis motors pins
#define IOPIN_Y_STEP D_PIN_51
#define IOPIN_Y_DIR D_PIN_50

// Z 1 axis motors pins
#define IOPIN_Z1_STEP D_PIN_47
#define IOPIN_Z1_DIR D_PIN_46

// Z 2 axis motors pins
#define IOPIN_Z2_STEP D_PIN_45
#define IOPIN_Z2_DIR D_PIN_44
/*================================================================*/

/*================================================================
    EXTRUDER
 =================================================================*/
// Extruders motors pins
#define IOPIN_E_STEP D_PIN_42
#define IOPIN_E_DIR D_PIN_43
/*================================================================*/

/*================================================================
    FAN
 =================================================================*/
#define IOPIN_FAN D_PIN_7
/*================================================================*/

/*================================================================
    THERMORESISTOR and Hoten
 =================================================================*/
#define IOPIN_HOTEND D_PIN_6
/*================================================================*/

/*================================================================
    THERMORESISTOR and Hoten
 =================================================================*/
#define IOPIN_AUTOLEVELING_SENSOR D_PIN_32
/*================================================================*/

/*================================================================
    LIMIT SWITCHS
 =================================================================*/
#define IOPIN_LIMITSWITCH_X_FOWARD D_PIN_2
#define IOPIN_LIMITSWITCH_X_BACKWARD D_PIN_3

#define IOPIN_LIMITSWITCH_Y_FOWARD D_PIN_20
#define IOPIN_LIMITSWITCH_Y_BACKWARD D_PIN_21
/*================================================================*/

/*================================================================
    LCD
 =================================================================*/
#define IOPIN_LCD_RS D_PIN_31
#define IOPIN_LCD_E D_PIN_30
#define IOPIN_LCD_D7 D_PIN_29
#define IOPIN_LCD_D6 D_PIN_28
#define IOPIN_LCD_D5 D_PIN_27
#define IOPIN_LCD_D4 D_PIN_26
#define IOPIN_LCD_D3 D_PIN_25
#define IOPIN_LCD_D2 D_PIN_24
#define IOPIN_LCD_D1 D_PIN_23
#define IOPIN_LCD_D0 D_PIN_22

/*================================================================*/
#define DEFINE_ALL_PINS                        \
    extern IOPin IOPIN_X_STEP;                 \
    extern IOPin IOPIN_Y_STEP;                 \
    extern IOPin IOPIN_Z1_STEP;                \
    extern IOPin IOPIN_Z2_STEP;                \
    extern IOPin IOPIN_E_STEP;                 \
    extern IOPin IOPIN_X_DIR;                  \
    extern IOPin IOPIN_Y_DIR;                  \
    extern IOPin IOPIN_Z1_DIR;                 \
    extern IOPin IOPIN_Z2_DIR;                 \
    extern IOPin IOPIN_E_DIR;                  \
    extern IOPin IOPIN_FAN;                    \
    extern IOPin IOPIN_HOTEND;                 \
    extern IOPin IOPIN_AUTOLEVELING_SENSOR;    \
    extern IOPin IOPIN_LIMITSWITCH_X_FOWARD;   \
    extern IOPin IOPIN_LIMITSWITCH_Y_FOWARD;   \
    extern IOPin IOPIN_LIMITSWITCH_X_BACKWARD; \
    extern IOPin IOPIN_LIMITSWITCH_Y_BACKWARD; \
    extern IOPin IOPIN_LCD_RS;                 \
    extern IOPin IOPIN_LCD_E;                  \
    extern IOPin IOPIN_LCD_D7;                 \
    extern IOPin IOPIN_LCD_D6;                 \
    extern IOPin IOPIN_LCD_D5;                 \
    extern IOPin IOPIN_LCD_D4;                 \
    extern IOPin IOPIN_LCD_D3;                 \
    extern IOPin IOPIN_LCD_D2;                 \
    extern IOPin IOPIN_LCD_D1;                 \
    extern IOPin IOPIN_LCD_D0;

DEFINE_ALL_PINS

#endif // __IOPINS_H__