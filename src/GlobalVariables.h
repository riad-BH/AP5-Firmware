#ifndef H_GLOBAL_VARIABLES
#define H_GLOBAL_VARIABLES


// Flag is set to 1 if bluetooth is activated
extern uint8_t FLAG_bluetoothState;
/************************************************/
// Flag is set to 1 if limit switch is activated
extern uint8_t FLAG_limitSwitchState;
/************************************************/

/*============================= char =============================*/
// Character array to store first elements like G0
char localBuffer[8];

/*================================================================*/

MouvementQueue mouvement_queue;
Motors steppers;
FastLCD lcd;

#endif // H_GLOBAL_VARIABLES