
/*================================================================
    INCLUDES AND DEFINES
 =================================================================*/
#include "Arduino.h"
#include "Config.h"
#include "Scheduler.h"

/*================================================================
    MAIN PROGRAM
 =================================================================*/

int main() {

  cli();
  setIO();
  setUSART0(USART_BAUD_RATE);
  sendStartingScreen();
  setTempControl();
  sei();

  while (1) {
    schedule();
  }

  return 0;
}

/*================================================================*/

#include "ISR.h"
