#include "RingBuffer.h"

RingBuffer::RingBuffer() : head(0), tail(0), head_pointer(0) {}

const char *RingBuffer::buffer_read()
{
  const char *t_buffer = NULL;
  if (data_available == 0)
  {
    sendLine("ERROR : Empty buffer");
    jumpLine();
    return t_buffer;
  }
  else
  {
    t_buffer = buffer[tail];
    tail = (tail + 1) % RING_BUFFER_SIZE;
    data_available--;
  }
  return t_buffer;
}

void RingBuffer::buffer_write(const char &charData, const char &charCompa)
{

  // if the current buffer is not full
  if (data_available < RING_BUFFER_SIZE)
  {
    buffer[head][head_pointer] = charData;
    if (charData == charCompa)
    {
      buffer[head][head_pointer + 1] = '\0';
      head = (head + 1) % RING_BUFFER_SIZE;
      head_pointer = 0;
      ++data_available;
      if (Flags::getFlag_machine() == 2)
      {
        Flags::setFlag_machine(RECEIVING);
      }
      RequestSender::setRequest_state(0);
      SerialReceiver::setReceiving_state(false);
      return;
    }
    head_pointer++;
  }
  else
  {
    sendLine("Ring buffer is full");
    jumpLine();
  }
}
