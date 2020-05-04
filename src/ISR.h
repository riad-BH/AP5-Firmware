#ifndef H_ISR
#define H_ISR
#include "LimitSwitch.h"
#include "Motors.h"
#include "Sending.h"
#include "TempControl.h"
#include "Usart.h"

// Service routine for Transmition USART_0
ISR(USART0_TX_vect) { SerialSender::transferData(); }

// Service routine for Reception USART_0
ISR(USART0_RX_vect) { SerialReceiver::fReceiving0(); }

/******************************************/

// Service routine for Reception USART_1
ISR(USART1_RX_vect) { SerialReceiver::fReceiving1(); }

// Service routine for Transmition USART_0
ISR(USART1_TX_vect) { SerialSender::transferData1(); }

/******************************************/

// 640 tics = 40 us
// X Y E MOTORS
ISR(TIMER1_COMPA_vect)
{
  steppers.moveSteppers(mouvement_queue);
}

// 640 tics = 40 us
// Z MOTOR
ISR(TIMER3_COMPA_vect)
{
}

/******************************************/
ISR(INT0_vect)
{
  LimitSwitchs::fLSFowardX(mouvement_queue);
  sendLine("INT0");
  jumpLine();
}

ISR(INT1_vect)
{
  LimitSwitchs::fLSBackwardX(mouvement_queue);
  sendLine("INT1");
  jumpLine();
}

ISR(INT4_vect)
{
  LimitSwitchs::fLSFowardY(mouvement_queue);
  sendLine("INT4");
  jumpLine();
}

ISR(INT5_vect)
{
  LimitSwitchs::fLSBackwardY(mouvement_queue);
  sendLine("INT5");
  jumpLine();
}
/********************************/

ISR(TIMER2_OVF_vect) { TempControl::timer2ISR(); }

ISR(ADC_vect) { BackgroundTasks::setTasksReady(); }

#endif // H_ISR
