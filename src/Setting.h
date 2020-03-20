#ifndef H_SETTING
#define H_SETTING

/*********************************************/
// #define _DEBUG
// #define _LIMITSWITCH
// #define _POSITIONS
// #define _BLUETOOTH
// #define _GET_EXTRUSION
#define _ABSOLUTE_POSITIONS
// #define _PROTEUS
// #define _ABSOLUTE_EXTRUSION
// #define _STEP_PER_MILIMETER_CALCULATION
#define _ACCELERATION_REDUCTOR
// #define _ACCELERATION_REDUCTOR_Z
// #define  _USE_fMoveExtruder
/*********************************************/
#define IMP_START 280
// 160 us = 40 mm/s
#define IMP_VALUE 107
#define IMP_VALUE_G0 107
// 2.5mm/s = 512
#define JERK_Z 512    
#define VELOCITY_Z 70 
#define VELOCITY_E 300
/*********************************************/
#define EXTRUDER_SPEED 15
/*********************************************/
#define ACCELERATION 1
#define ACCELERATION_Z 2
/*********************************************/
#define ACCELERATION_FACTOR 1
/*********************************************/
#define MIN_X -270
#define MAX_X 270
#define MIN_Y -270
#define MAX_Y 270
#define MIN_Z -170
#define MAX_Z 170
/*********************************************/
#define STEP_PER_MILLIMETER_X 160
#define STEP_PER_MILLIMETER_Y 160
#define STEP_PER_MILLIMETER_Z 400
/*********************************************/
#define MANUAL_CONTROL_STEP 10
/*********************************************/
#define USART_BAUD_RATE 500000
/*********************************************/
#define BLUETOOTH_BAUD_RATE 9600
/*********************************************/
#define TEMPERATURE 200
/*********************************************/
#define EXTRUDER_GEAR_COEFFICIENT 291
/*********************************************/
#endif