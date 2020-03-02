#include "Usart.h"

void setUSART0(const uint32_t baudRate)
{
  UBRR0 = (uint16_t)((1000000 / baudRate) - 1);
  //UBRR0 = 3;
  // Asynchronous mode
  UCSR0C = 0;
  // Parity mode disabled
  UCSR0C = 0;
  // Stop bits 1
  UCSR0C = 0;
  // Data size
  UCSR0C |= (_BV(UCSZ00) | _BV(UCSZ01));
  // Transmitter enable
  UCSR0B = _BV(TXEN0);
  // Reception Interrupt Complete Enable and Recieve Enable
  UCSR0B |= _BV(RXCIE0) | _BV(RXEN0);
}

void setUSART1(const uint16_t baudRate)
{
  UBRR1 = (uint16_t)(1000000 / baudRate) - 1;
  // Asynchronous mode
  UCSR1C = 0;
  // Parity mode disabled
  UCSR1C = 0;
  // Stop bits 1
  UCSR1C = 0;
  // Data size
  UCSR1C |= (_BV(UCSZ10) | _BV(UCSZ11));
  // Transmitter enable
  UCSR1B = _BV(TXEN0);
  // Reception Interrupt Complete Enable and Recieve Enable
  UCSR1B |= _BV(RXCIE1) | _BV(RXEN1);
}

void unsetUSART1()
{
  UCSR1B = 0;
}