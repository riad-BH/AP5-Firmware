#ifndef __BACKGROUNDTASKS_H__
#define __BACKGROUNDTASKS_H__

#include "Arduino.h"
#include "FastLCD.h"
#include "TempControl.h"
#include "intervalBinarySearch.h"
#include "Pins.h"

extern FastLCD lcd;

class BackgroundTasks
{
private:
  static uint8_t task_pointer;

public:
  static inline void executeTask()
  {

    switch (task_pointer)
    {
    case 1:
      TempControl::regulateTemp();
      task_pointer++;
      break;

    case 2:
      TempControl::voltageToResistance();
      task_pointer++;
      break;

    case 3:
      intervalBinarySearch::search<291>(TempControl::temperature_array, TempControl::resistance_read);
      task_pointer++;
      break;

    case 4:
      lcd.sendData(intervalBinarySearch::return_value);
      task_pointer = 0;
      lcd.resetCursor();
      break;

    default:
      break;
    }
  }

  static inline void setTasksReady()
  {
    task_pointer = 1;
  }

  static inline uint8_t areTasksReady()
  {
    return task_pointer;
  }
};
#endif // __BACKGROUNDTASKS_H__