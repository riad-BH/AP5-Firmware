#include "Sending.h"

/*************** Local Variables ****************/
// Pointer for the transmition string
static uint8_t TX_stringPointer = 0;
// Flag that states if there is an available data for transmition
static uint8_t FLAG_bufferReady = 0;
// String to store the data for transmition
static String TX_inputString;
// Pointer for the transmition string
static uint8_t TX_stringPointer1 = 0;
// Flag that states if there is an available data for transmition
static uint8_t FLAG_bufferReady1 = 0;
// String to store the data for transmition
static String TX_inputString1;
/************************************************/

/********************************************************************/
void sendData(String localString)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += localString;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += localString;
  }
}
/********************************************************************/

void sendData(float *localFloat)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += (*localFloat);
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += (*localFloat);
  }
}
/********************************************************************/

void sendData(uint8_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/

void sendData(int8_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/

void sendData(uint16_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/

void sendData(int16_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/

void sendData(volatile uint16_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/

void sendData(uint32_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/

void sendData(int32_t *localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += *localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += *localInt;
  }
}
/********************************************************************/
void sendData(int8_t localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += localInt;
  }
}
/********************************************************************/
void sendData(int16_t localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += localInt;
  }
}
/********************************************************************/
void sendData(int32_t localInt)
{
  if (!FLAG_bufferReady)
  {
    FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    TX_inputString += localInt;
    if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
    {
      UDR0 = TX_inputString[TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      FLAG_bufferReady = 0;
      TX_stringPointer = 0;
      TX_inputString = "";
    }
  }
  else
  {
    TX_inputString += localInt;
  }
}
/********************************************************************/

void transferData()
{
  if (FLAG_bufferReady && TX_inputString[TX_stringPointer] != 0)
  {
    UDR0 = TX_inputString[TX_stringPointer++];
  }
  else
  {
    UCSR0B &= ~_BV(TXCIE0);
    FLAG_bufferReady = 0;
    TX_stringPointer = 0;
    TX_inputString = "";
  }
}

/*
  **************************************************************************************
*/

/********************************************************************/
void sendData1(String localString)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += localString;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += localString;
  }
}
/********************************************************************/

void sendData1(float *localFloat)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += (*localFloat);
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += (*localFloat);
  }
}
/********************************************************************/

void sendData1(uint8_t *localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += *localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += *localInt;
  }
}
/********************************************************************/

void sendData1(int8_t *localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += *localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += *localInt;
  }
}
/********************************************************************/

void sendData1(uint16_t *localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += *localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += *localInt;
  }
}
/********************************************************************/

void sendData1(int16_t *localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += *localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += *localInt;
  }
}
/********************************************************************/

void sendData1(uint32_t *localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += *localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += *localInt;
  }
}
/********************************************************************/

void sendData1(int32_t *localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += *localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += *localInt;
  }
}

/********************************************************************/
void sendData1(int8_t localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += localInt;
  }
}
/********************************************************************/
void sendData1(int16_t localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += localInt;
  }
}
/********************************************************************/
void sendData1(int32_t localInt)
{
  if (!FLAG_bufferReady1)
  {
    FLAG_bufferReady1 = 1;
    UCSR1B |= _BV(TXCIE1);
    TX_inputString1 += localInt;
    if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
    {
      UDR1 = TX_inputString1[TX_stringPointer1++];
    }
    else
    {
      UCSR1B &= ~_BV(TXCIE1);
      FLAG_bufferReady1 = 0;
      TX_stringPointer1 = 0;
      TX_inputString1 = "";
    }
  }
  else
  {
    TX_inputString1 += localInt;
  }
}
/********************************************************************/

void transferData1()
{
  if (FLAG_bufferReady1 && TX_inputString1[TX_stringPointer1] != 0)
  {
    UDR1 = TX_inputString1[TX_stringPointer1++];
  }
  else
  {
    UCSR1B &= ~_BV(TXCIE1);
    FLAG_bufferReady1 = 0;
    TX_stringPointer1 = 0;
    TX_inputString1 = "";
  }
}
/********************************************************************/