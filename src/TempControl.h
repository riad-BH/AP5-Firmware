#if !defined(H_TEMPCONTROL)
#define H_TEMPCONTROL

#include "ADC.h"
#include "Arduino.h"
#include "Pins.h"
#include "Sending.h"
#include "Setting.h"
#include "TimerSetting.h"
#include "intervalBinarySearch.h"

class BackgroundTasks;

class TempControl
{

private:
  static uint32_t resistance_read;
  static uint16_t temperature_read;
  static uint16_t set_temperature;
  static int16_t PID_error;
  static int16_t previous_error;
  static const uint8_t elapsedTime;
  static int16_t PID_value;

  // PID constants
  static const uint8_t KP = 30;
  static const uint8_t KI = 0;
  static const uint8_t KD = 150;

  // PID values
  static int16_t PID_p;
  static int16_t PID_i;
  static int16_t PID_d;

  // Flag active if there the adc has finished the conversion
  volatile static uint8_t Flag_ADC;
  // Flag active if there the adc has finished the conversion
  volatile static uint16_t timer2_counter;

  static const uint32_t PROGMEM temperature_array[291][2];

public:
  static void setTempControl();

  static void setTemperature(const uint16_t &);

  static void regulateTemp();

  static void voltageToResistance();

  // inline static void setFlagADC() { Flag_ADC = true; }

  // static void inline resetFlagADC() { Flag_ADC = false; }

  // static inline volatile uint8_t &readFlagADC() { return Flag_ADC; }

  static void inline timer2ISR()
  {
    timer2_counter++;
    if (timer2_counter == CYCLES_TO_ONE_SECOND)
    {
      ADCSRA |= _BV(ADSC);
      timer2_counter = 0;
    }
  }

  friend class BackgroundTasks;
};

#endif // H_TEMPCONTROL
