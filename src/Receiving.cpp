#include "Receiving.h"

/*************** Local Variables ****************/
// Flag that indicates array 1 is receiving data
static volatile uint8_t FLAG_RX_array1_ON = 1;
// Flag that indicates array 2 is receiving data
static volatile uint8_t FLAG_RX_array2_ON = 0;
/************************************************/

/*************** Extern Variables ***************/
// Character array to store the first next line
extern char RX_array1[128];
// Character array to store the second next line
extern char RX_array2[128];
/************************************************/
// Flag is set to :
//# 0 == RX_array1 empty
//# 1 == RX_array1 full
//# 2 == RX_array1 processed
extern uint8_t FLAG_RX_array1_state;
// Flag is set to :
//# 0 == RX_array2 empty
//# 1 == RX_array2 full
//# 2 == RX_array2 processed
extern uint8_t FLAG_RX_array2_state;
/************************************************/
// Pointer for the volatile reception string
extern volatile uint8_t RX_volatilePointer;
/************************************************/
// Flag that indicates that a data has ben recieved and it's ready to be
// processed
extern volatile uint8_t FLAG_RX;
/************************************************/

/*************** Extern Function ***************/
// Function to send data USART_0
extern void sendData(String);
extern void sendData(float *);
extern void sendData(uint8_t *);
extern void sendData(int8_t *);
extern void sendData(uint16_t *);
extern void sendData(int16_t *);
extern void sendData(uint32_t *);
extern void sendData(int32_t *);
extern void sendData(int8_t);
extern void sendData(int16_t);
extern void sendData(int32_t);
/************************************************/

void fReceiving0()
{
  // Receiving in the first array
  if (!FLAG_RX_array2_ON && !FLAG_RX_array1_state)
  {
    FLAG_RX_array1_ON = 1;
    RX_array1[RX_volatilePointer] = UDR0;
#ifdef _PROTEUS
    if (RX_array1[RX_volatilePointer] == '\r')
    {
      #ifdef _DEBUG
      sendData("_1\r");
      #endif
      RX_array1[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array1_state = FULL;
      FLAG_RX_array1_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
#else
    if (RX_array1[RX_volatilePointer] == '\n')
    {
      RX_array1[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array1_state = FULL;
      FLAG_RX_array1_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
#endif
  }
  // Receiving in the second array
  else if (!FLAG_RX_array1_ON && !FLAG_RX_array2_state)
  {
    FLAG_RX_array2_ON = 1;
    RX_array2[RX_volatilePointer] = UDR0;
#ifdef _PROTEUS
    if (RX_array2[RX_volatilePointer] == '\r')
    {
       #ifdef _DEBUG
      sendData("_2\r");
      #endif
      RX_array2[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array2_state = FULL;
      FLAG_RX_array2_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
  }
#else
    if (RX_array2[RX_volatilePointer] == '\n')
    {
      RX_array2[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array2_state = FULL;
      FLAG_RX_array2_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
  }
#endif
}
/************************************************/
void fReceiving1()
{
  // Receiving in the first array
  if (!FLAG_RX_array2_ON && !FLAG_RX_array1_state)
  {
    FLAG_RX_array1_ON = 1;
    RX_array1[RX_volatilePointer] = UDR1;
#ifdef _PROTEUS
    if (RX_array1[RX_volatilePointer] == '\r')
    {
      RX_array1[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array1_state = FULL;
      FLAG_RX_array1_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
#else
    if (RX_array1[RX_volatilePointer] == '\n')
    {
      RX_array1[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array1_state = FULL;
      FLAG_RX_array1_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
#endif
  }
  // Receiving in the second array
  else if (!FLAG_RX_array1_ON && !FLAG_RX_array2_state)
  {
    FLAG_RX_array2_ON = 1;
    RX_array2[RX_volatilePointer] = UDR1;
#ifdef _PROTEUS
    if (RX_array2[RX_volatilePointer] == '\r')
    {
      RX_array2[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array2_state = FULL;
      FLAG_RX_array2_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
  }
#else
    if (RX_array2[RX_volatilePointer] == '\n')
    {
      RX_array2[++(RX_volatilePointer)] = '\0';
      FLAG_RX_array2_state = FULL;
      FLAG_RX_array2_ON = 0;
      FLAG_RX = 1;
    }
    else
    {
      RX_volatilePointer++;
    }
  }
#endif
}
/************************************************/