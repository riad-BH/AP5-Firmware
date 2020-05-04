#ifndef H_SENDING
#define H_SENDING
#include "Setting.h"
#include <Arduino.h>
//SerialSender
class SerialSender
{
private:
  // Pointer for the transmition string
  static uint16_t TX_stringPointer;
  // Flag that states if there is an available data for transmition
  static uint8_t FLAG_bufferReady;
  // String to store the data for transmition
  static String TX_inputString;
  // Pointer for the transmition string
  static uint8_t TX_stringPointer1;
  // Flag that states if there is an available data for transmition
  static uint8_t FLAG_bufferReady1;
  // String to store the data for transmition
  static String TX_inputString1;

public:
  // Function for the interruption to send data USART_0
  static void transferData();

  // Function for the interruption to send data USART_1
  static void transferData1();

  template <typename T>
  friend void sendData(T *);

  template <typename T>
  friend void sendData(const T &);
};

template <typename T>
void sendData(T *localString)
{
  if (!SerialSender::FLAG_bufferReady)
  {
    SerialSender::FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    SerialSender::TX_inputString += *localString;
    if (SerialSender::FLAG_bufferReady &&
        SerialSender::TX_inputString
                [SerialSender::TX_stringPointer] != 0)
    {
      UDR0 = SerialSender::TX_inputString
          [SerialSender::TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      SerialSender::FLAG_bufferReady = 0;
      SerialSender::TX_stringPointer = 0;
      SerialSender::TX_inputString = "";
    }
  }
  else
  {
    SerialSender::TX_inputString += *localString;
  }
}

template <typename T>
void sendData(const T &localString)
{

  if (!SerialSender::FLAG_bufferReady)
  {
    SerialSender::FLAG_bufferReady = 1;
    UCSR0B |= _BV(TXCIE0);
    SerialSender::TX_inputString += localString;
    if (SerialSender::FLAG_bufferReady &&
        SerialSender::TX_inputString
                [SerialSender::TX_stringPointer] != 0)
    {
      UDR0 = SerialSender::TX_inputString
          [SerialSender::TX_stringPointer++];
    }
    else
    {
      UCSR0B &= ~_BV(TXCIE0);
      SerialSender::FLAG_bufferReady = 0;
      SerialSender::TX_stringPointer = 0;
      SerialSender::TX_inputString = "";
    }
  }
  else
  {
    SerialSender::TX_inputString += localString;
  }
}

void inline sendLine(const char *str) { sendData<const char *>(str); }

// Jump line function
#if _PROTEUS == 1
void inline jumpLine()
{
  sendLine("\r");
}
#else
void inline jumpLine()
{
  sendLine("\n");
}
#endif

#endif // H_SENDING