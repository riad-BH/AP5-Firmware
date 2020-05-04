#ifndef H_PIN_FUNCTIONS
#define H_PIN_FUNCTIONS

/*                            PORT A                              */
/*================================================================*/

#define A_OUTPUT(pinName) \
  DDRA |= _BV(pinName);   \
  PORTA &= ~_BV(pinName);

#define A_INPUT_PULLUP(pinName) \
  DDRA &= ~_BV(pinName);        \
  PORTA |= _BV(pinName);
/*================================================================*/

/*                            PORT B                              */
/*================================================================*/

#define B_OUTPUT(pinName) \
  DDRB |= _BV(pinName);   \
  PORTB &= ~_BV(pinName);

#define B_INPUT_PULLUP(pinName) \
  DDRB &= ~_BV(pinName);        \
  PORTB |= _BV(pinName);
/*================================================================*/

/*                            PORT C                              */
/*================================================================*/
// For PORT C
#define C_OUTPUT(pinName) \
  DDRC |= _BV(pinName);   \
  PORTC &= ~_BV(pinName);

#define C_INPUT_PULLUP(pinName) \
  DDRC &= ~_BV(pinName);        \
  PORTC |= _BV(pinName);

#define C_INPUT(pinName) \
  DDRC &= ~_BV(pinName);
/*================================================================*/

/*                            PORT D                              */
/*================================================================*/
// For PORT D
#define D_OUTPUT(pinName) \
  DDRD |= _BV(pinName);   \
  PORTD &= ~_BV(pinName);

#define D_INPUT_PULLUP(pinName) \
  DDRD &= ~_BV(pinName);        \
  PORTD |= _BV(pinName);
/*================================================================*/

/*                            PORT E                              */
/*================================================================*/
// For PORT E
#define E_OUTPUT(pinName) \
  DDRE |= _BV(pinName);   \
  PORTE &= ~_BV(pinName);

#define E_INPUT_PULLUP(pinName) \
  DDRE &= ~_BV(pinName);        \
  PORTE |= _BV(pinName);
/*================================================================*/

/*                            PORT F                              */
/*================================================================*/
// For PORT F
#define F_OUTPUT(pinName) \
  DDRF |= _BV(pinName);   \
  PORTF &= ~_BV(pinName);

#define F_INPUT_PULLUP(pinName) \
  DDRF &= ~_BV(pinName);        \
  PORTF |= _BV(pinName);
/*================================================================*/

/*                            PORT G                              */
/*================================================================*/
// For PORT G
#define G_OUTPUT(pinName) \
  DDRG |= _BV(pinName);   \
  PORTG &= ~_BV(pinName);

#define G_INPUT_PULLUP(pinName) \
  DDRG &= ~_BV(pinName);        \
  PORTG |= _BV(pinName);
/*================================================================*/

/*                            PORT H                             */
/*================================================================*/
// For PORT H
#define H_OUTPUT(pinName) \
  DDRH |= _BV(pinName);   \
  PORTH &= ~_BV(pinName);

#define H_INPUT_PULLUP(pinName) \
  DDRH &= ~_BV(pinName);        \
  PORTH |= _BV(pinName);
/*================================================================*/

/*                            PORT J                              */
/*================================================================*/
// For PORT J
#define J_OUTPUT(pinName) \
  DDRJ |= _BV(pinName);   \
  PORTJ &= ~_BV(pinName);

#define J_INPUT_PULLUP(pinName) \
  DDRJ &= ~_BV(pinName);        \
  PORTJ |= _BV(pinName);
/*================================================================*/

/*                            PORT K                              */
/*================================================================*/
// For PORT K
#define K_OUTPUT(pinName) \
  DDRK |= _BV(pinName);   \
  PORTK &= ~_BV(pinName);

#define K_INPUT_PULLUP(pinName) \
  DDRK &= ~_BV(pinName);        \
  PORTK |= _BV(pinName);
/*================================================================*/

/*                            PORT L                              */
/*================================================================*/
// For PORT L
#define L_OUTPUT(pinName) \
  DDRL |= _BV(pinName);   \
  PORTL &= ~_BV(pinName);

#define L_INPUT_PULLUP(pinName) \
  DDRL &= ~_BV(pinName);        \
  PORTL |= _BV(pinName);
/*================================================================*/

#endif // H_PIN_FUNCTIONS