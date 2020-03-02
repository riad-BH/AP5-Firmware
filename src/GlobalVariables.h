#ifndef H_GLOBAL_VARIABLES
#define H_GLOBAL_VARIABLES

/*============================= INT ==============================*/

// Pointer for the reception string
uint8_t RX_stringPointer = 0;
// Pointer for the volatile reception string
volatile uint8_t RX_volatilePointer = 0;
// Flag is set to 1 if bluetooth is activated
extern uint8_t FLAG_bluetoothState;
/************************************************/
// Flag is set to 1 if limit switch is activated
extern uint8_t FLAG_limitSwitchState;
/************************************************/
// X
int32_t dx = 0;
// Y
int32_t dy = 0;
// Z
int32_t dz = 0;

/*================================================================*/

/*============================ FLOAT =============================*/
// Accual X position
float xPos = 0;

// Accual Y position
float yPos = 0;

// Accual Z position
float zPos = 0;
/*================================================================*/

/*============================= char =============================*/
// Character array to store first elements like G0
char localBuffer[8];

// Character array to store the first next line
char RX_array1[128];

// Character array to store the second next line
char RX_array2[128];

// Character array to store the recieved data
char RX_inputString[128];

// Character for storing the recieved data
volatile char RX_data = 0;
/*================================================================*/

#endif // H_GLOBAL_VARIABLES