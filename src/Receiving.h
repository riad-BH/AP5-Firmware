#ifndef H_RECEIVING
#define H_RECEIVING

#include "Arduino.h"
#include "RingBuffer.h"

class SerialReceiver
{

private:
  static RingBuffer RX_queue;

  // if set to 1 : there is an incomming data
  // if set to 0 : there is not an incomming data
  static volatile bool receiving_state;

public:
  static void fReceiving0();
  static void fReceiving1();

  static inline const char *readBuffer() { return RX_queue.buffer_read(); }

  static inline const uint8_t &data_available()
  {
    return RX_queue.ringBuffer_available_data();
  }

  static inline void setReceiving_state(const bool &rs)
  {
    receiving_state = rs;
  }

  static inline const volatile bool &getReceiving_state()
  {
    return receiving_state;
  }
};

#endif // H_RECEIVING