#if !defined(H_SCHEDULER)
#define H_SCHEDULER

#include "Arduino.h"
#include "Config.h"
#include "ConstDefines.h"
#include "Flags.h"
#include "GlobalVariables.h"

/*================================================================*/

void inline schedule() {
  switch (FLAG_machine) {

  /* RECEIVING */
  case 0:
    if (FLAG_RX) {
      RX_stringPointer = RX_volatilePointer;
      RX_volatilePointer = 0;
      FLAG_machine = PROCESSING; // Next step activated
      FLAG_RX = 0;
    } else if (readFlagADC()) {
      regulateTemp();
    }
    break;

  /* PROCESSING */
  case 1:
    // PORTL |= _BV(PIN_Z_STEP);
    if (FLAG_RX_array1_state == FULL) {
      if (!fProcessing(RX_array1, localBuffer, &dx, &dy, &dz)) {
        FLAG_RX_array1_state = PROCESSED;
        FLAG_array1_or_array2 = ARRAY_1;
        fAccelCompute(&dx, &dy, &dz);
        FLAG_machine = ACTION; // Next step activated
      } else {
        FLAG_RX_array1_state = EMPTY;
        FLAG_machine = RECEIVING;
      }
    } else if (FLAG_RX_array2_state == FULL) {
      if (!fProcessing(RX_array2, localBuffer, &dx, &dy, &dz)) {
        FLAG_RX_array2_state = PROCESSED;
        FLAG_array1_or_array2 = ARRAY_2;
        fAccelCompute(&dx, &dy, &dz);
        FLAG_machine = ACTION; // Next step activated
      } else {
        FLAG_RX_array2_state = EMPTY;
        FLAG_machine = RECEIVING;
      }
    } else {
      FLAG_machine = RECEIVING; // Go back to 0
    }

    break;

  /* SETTING UP AND ACTION */
  case 2:
    if (!FLAG_motorsActivated) {
      fSettingUp();
#ifdef _PROTEUS
      sendData(">\r");
#else
      sendData(">\n");
#endif
      FLAG_machine = RECEIVING; // Go back to 0
    } else if (readFlagADC()) {
      regulateTemp();
    }
    break;

  /*DEFAULT */
  default:
    sendData("State error");
    jumpLine();
    break;
  }
}

#endif // H_SCHEDULER
