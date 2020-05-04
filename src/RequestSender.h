#if !defined(H_REQUESTSENDER)
#define H_REQUESTSENDER

#include "Arduino.h"
#include "Sending.h"
#include "Macro.h"

class RequestSender
{

private:
  // if set to 1 : a request was sent
  // if set to 0 : no request was sent
  static volatile uint8_t request_state;

public:
  static inline void setRequest_state(const uint8_t &rs) { request_state = rs; }

  static inline const volatile uint8_t &getRequest_state()
  {
    return request_state;
  }

  static inline void sendRequest()
  {
    setRequest_state(1);
   
#if _PROTEUS == 1
    sendLine(">\r");
#else
    sendLine(">\n");
#endif

  }
};

#endif // H_REQUESTSENDER
