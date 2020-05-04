#include "Sending.h"

// Pointer for the transmition string
uint16_t SerialSender::TX_stringPointer = 0;
// Flag that states if there is an available data for transmition
uint8_t SerialSender::FLAG_bufferReady = 0;
// String to store the data for transmition
String SerialSender::TX_inputString;
// Pointer for the transmition string
uint8_t SerialSender::TX_stringPointer1 = 0;
// Flag that states if there is an available data for transmition
uint8_t SerialSender::FLAG_bufferReady1 = 0;
// String to store the data for transmition
String SerialSender::TX_inputString1;

/********************************************************************/

void SerialSender::transferData()
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

void SerialSender::transferData1()
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