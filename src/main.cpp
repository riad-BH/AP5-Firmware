
/*================================================================
    INCLUDES AND DEFINES
 =================================================================*/
#include "Arduino.h"
#include "Config.h"
#include "Scheduler.h"
#include "IOFunctions.h"

/*================================================================
    MAIN PROGRAM
 =================================================================*/

int main()
{

  ENTER_LV1_CRITICAL_SECTION;
  setIO();
  setUSART0(USART_BAUD_RATE);
  sendStartingScreen();
  TempControl::setTempControl();
  lcd.configure();

 EXIT_LV1_CRITICAL_SECTION;

  while (1)
  {
    Scheduler::schedule();
  }

  return 0;
}

/*================================================================*/

#include "ISR.h"
