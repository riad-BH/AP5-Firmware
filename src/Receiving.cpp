#include "Receiving.h"

RingBuffer SerialReceiver::RX_queue = RingBuffer();

volatile bool SerialReceiver::receiving_state = false;

void SerialReceiver::fReceiving0()
{
  SerialReceiver::setReceiving_state(true);
#if _PROTEUS == 1
  RX_queue.buffer_write(UDR0, '\r');
#else
  RX_queue.buffer_write(UDR0, '\n');
#endif
}
/************************************************/

void SerialReceiver::fReceiving1()
{
#if _PROTEUS == 1
  RX_queue.buffer_write(UDR1, '\r');
#else
  RX_queue.buffer_write(UDR1, '\n');
#endif
}
/************************************************/