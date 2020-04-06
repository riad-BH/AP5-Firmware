#include "TempControl.h"

static uint16_t temperature_read = 0;
static uint16_t set_temperature = TEMPERATURE;
static int16_t PID_error = 0;
static int16_t previous_error = 0;
static const uint8_t elapsedTime = 1;
static int16_t PID_value = 0;

// PID constants
static const uint8_t kp = 30;
static const uint8_t ki = 0;
static const uint8_t kd = 150;

// PID values
static int16_t PID_p = 0;
static int16_t PID_i = 0;
static int16_t PID_d = 0;

// Flag active if there the adc has finished the conversion
volatile static uint8_t Flag_ADC = 0;
// Flag active if there the adc has finished the conversion
volatile static uint16_t timer2_counter = 0;

void regulateTemp() {
  //PORTB ^= _BV(PIN_X_STEP);
  temperature_read = ADC;
  sendData("$T");
  sendData(&temperature_read);
  jumpLine();
  PID_error = set_temperature - temperature_read;
  PID_p = PID_error * kp;
  PID_d = ((PID_error - previous_error) / elapsedTime) * kd;
  PID_value = PID_p + PID_i + PID_d;

  if (PID_value < 0) {
    PID_value = 0;
  } else if (PID_value > 255) {
    PID_value = 255;
  }

  OCR4A = 255 - PID_value;
  previous_error = PID_error;
  resetFlagADC();
   //PORTB ^= _BV(PIN_X_STEP);
}

void setTempControl() {
  setTimer2();
  setTimer4();
  setADC();
}

void setTemperature(uint16_t temperature){
set_temperature = temperature;
}

void  timer2ISR() {
  timer2_counter++;
  if (timer2_counter == CYCLES_TO_ONE_SECOND) {
    ADCSRA |= _BV(ADSC);
    timer2_counter = 0;
  }
}

void  setFlagADC() { Flag_ADC = true; }

void  resetFlagADC() { Flag_ADC = false; }

uint8_t readFlagADC() { return Flag_ADC; }