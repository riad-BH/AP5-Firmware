#if !defined(H_SCHEDULER)
#define H_SCHEDULER

#include "Arduino.h"
#include "Config.h"
#include "ConstDefines.h"
#include "Flags.h"
#include "FastLCD.h"
#include "GlobalVariables.h"
#include "Mouvement.h"
#include "RequestSender.h"
#include "Setting.h"
#include "BackgroundTasks.h"

/*================================================================*/
class Scheduler
{
public:
  static void inline sendRequestSubTask()
  {
     ENTER_LV1_CRITICAL_SECTION;
    if (!SerialReceiver::getReceiving_state() && !RequestSender::getRequest_state() && SerialReceiver::data_available() < RING_BUFFER_SIZE)
    {
    
      RequestSender::sendRequest();
    }
    EXIT_LV1_CRITICAL_SECTION;
  }

  static void inline receiveTask()
  {
    if (SerialReceiver::data_available() > 0)
    {
      sendRequestSubTask();
      // Next step activated
      Flags::setFlag_machine(PROCESSING);
    }
    else if (BackgroundTasks::areTasksReady())
    {
      BackgroundTasks::executeTask();
    }
  }

  static void inline processTask()
  {
    if (mouvement_queue.getAvailable_mouvement() == RING_BUFFER_SIZE)
    {
      Flags::setFlag_machine(ACTION);
      return;
    }

    if (!fProcessing(SerialReceiver::readBuffer(), localBuffer,
                     mouvement_queue))
    {

      advancedProcessing(mouvement_queue);

      Flags::setFlag_machine(ACTION);
    }
    else
    {
      Flags::setFlag_machine(RECEIVING);
    }
  }

  static void inline moveSteppersTask()
  {
    if (!Flags::getFlag_motor_activated() &&
        !Flags::getFlag_motor_z_activated() &&
        (mouvement_queue.getAvailable_mouvement() != 0))
    {
      steppers.mouvementSorter(mouvement_queue);
    }
    else if (BackgroundTasks::areTasksReady())
    {
      BackgroundTasks::executeTask();
    }
    Flags::setFlag_machine(RECEIVING);
  }

  static void inline schedule()
  {
    switch (Flags::getFlag_machine())
    {
    case 0:
      /* RECEIVING */
      receiveTask();
      break;

    case 1:
      /* PROCESSING */
      processTask();
      break;

    case 2:
      /* ACTION*/
      moveSteppersTask();
      break;

    /*DEFAULT */
    default:
      sendLine("State error");
      jumpLine();
      break;
    }
  }
};

#endif // H_SCHEDULER
