#ifndef H_ISR
#define H_ISR
#include "LimitSwitch.h"
#include "Motors.h"
#include "Sending.h"
#include "TempControl.h"
#include "Usart.h"

// Flag set on if there is an extrusion
extern uint8_t FLAG_extrusion_for_timer;
// Flag active if adc is available
extern volatile uint8_t flag_adc;

// Service routine for Transmition USART_0
ISR(USART0_TX_vect) { transferData(); }

// Service routine for Reception USART_0
ISR(USART0_RX_vect) { fReceiving0(); }

/******************************************/

// Service routine for Reception USART_1
ISR(USART1_RX_vect) { fReceiving1(); }

// Service routine for Transmition USART_0
ISR(USART1_TX_vect) { transferData1(); }

/******************************************/

// 640 tics = 40 us
// X Y E MOTORS
ISR(TIMER1_COMPA_vect) { fMoveXYE(); }

// 640 tics = 40 us
// Z MOTOR
ISR(TIMER3_COMPA_vect) {
  if (FLAG_extrusion_for_timer) {
    fMoveE();
  } else {
    fMoveZ();
  }
}

/******************************************/
ISR(INT0_vect) {
  fLSFowardX();
  sendData("INT0");
  jumpLine();
}

ISR(INT1_vect) {
  fLSBackwardX();
  sendData("INT1");
  jumpLine();
}

ISR(INT4_vect) {
  fLSFowardY();
  sendData("INT4");
  jumpLine();
}

ISR(INT5_vect) {
  fLSBackwardY();
  sendData("INT5");
  jumpLine();
}
/********************************/

ISR(TIMER2_OVF_vect) { timer2ISR(); }

ISR(ADC_vect) { setFlagADC(); }

#endif // H_ISR
