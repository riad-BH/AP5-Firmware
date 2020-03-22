#include "ADC.h"
void setADC(){
    // Vref configuration
  ADMUX = ( _BV(REFS0) );
  // ADC ENABLE , AUTO TRIGGER ENABLE | _BV(ADATE) , INT ENABLE , PRESCALER
  ADCSRA = (_BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0));
  // ADC DISABLE DIGITAL PIN IN ADC0
  DIDR0 |= _BV(ADC0D);
  // Activate the ADC
  ADCSRA |= _BV(ADSC);
}