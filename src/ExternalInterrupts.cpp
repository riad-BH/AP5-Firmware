#include "ExternalInterrupts.h"

void setInt(uint8_t intePin)
{
  switch (intePin)
  {
  case 0:
    EICRA |= _BV(ISC01);
    EIMSK |= _BV(INT0);
    break;
  case 1:
    EICRA |= _BV(ISC11);
    EIMSK |= _BV(INT1);
    break;
  case 2:
    EICRA |= _BV(ISC21);
    EIMSK |= _BV(INT2);
    break;
  case 3:
    EICRA |= _BV(ISC31);
    EIMSK |= _BV(INT3);
    break;
  case 4:
    EICRB |= _BV(ISC41);
    EIMSK |= _BV(INT4);
    break;
  case 5:
    EICRB |= _BV(ISC51);
    EIMSK |= _BV(INT5);
    break;
  default:
    break;
  }
}

void unsetInt(uint8_t intePin)
{
  switch (intePin)
  {
  case 0:
    EICRA = 0;
    EIMSK = 0;
    break;
  case 1:
    EICRA = 0;
    EIMSK = 0;
    break;
  case 2:
    EICRA = 0;
    EIMSK = 0;
    break;
  case 3:
    EICRA = 0;
    EIMSK = 0;
    break;
  case 4:
    EICRB = 0;
    EIMSK = 0;
    break;
  case 5:
    EICRB = 0;
    EIMSK = 0;
    break;
  default:
    break;
  }
}
