#if !defined(H_RINGBUFFER)
#define H_RINGBUFFER

#include "Arduino.h"
#include "Setting.h"
#include "RequestSender.h"
#include "Sending.h"
#include "ConstDefines.h"
#include "Flags.h"
#include "Pins.h"

class RingBuffer
{
public:
  RingBuffer();

  void buffer_write(const char &, const char &);

  const char *buffer_read();

  const char &buffer_last_char();

  inline const uint8_t &ringBuffer_available_data()
  {
    return data_available;
  }

private:
  // Head always points to the next empty cell
  // Head is used to write new data to the buffer
  // initialized with 0
  uint8_t head = 0;

  // Tail always points to an unread cell
  // Tail is used to read new data from the buffer
  // initialized with 0
  uint8_t tail = 0;

  uint8_t head_pointer = 0;

  // buffer
  char buffer[RING_BUFFER_SIZE][BUFFER_SIZE];

  uint8_t data_available = 0;
};

#include "Receiving.h"

#endif // H_RINGBUFFER
