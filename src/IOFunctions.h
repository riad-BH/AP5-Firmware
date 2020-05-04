#ifndef __IOFUNCTIONS_H__
#define __IOFUNCTIONS_H__

#include "Arduino.h"
#include "PinMega.h"
#include "Sending.h"

#define MODE_INPUT 0
#define MODE_OUTPUT 1
#define MODE_INPUT_PULLUP 2

#define OUTPUT_LOW 0
#define OUTPUT_HIGH 1

#define CODE_PORTA 1
#define CODE_PORTB 2
#define CODE_PORTC 3
#define CODE_PORTD 4
#define CODE_PORTE 5
#define CODE_PORTF 6
#define CODE_PORTG 7
#define CODE_PORTH 8
#define CODE_PORTJ 9
#define CODE_PORTK 10
#define CODE_PORTL 11

class IOPin
{
public:
	const uint8_t pin_number;
	const uint8_t pin_port;
	constexpr IOPin(const uint8_t pn, const uint8_t pp) : pin_number(pn), pin_port(pp)
	{
	}
};

template <IOPin &IOP>
class IOPort
{
private:
	IOPort();

public:

	inline static constexpr void IOConfiguration(const uint8_t mode)
	{
		if (mode == MODE_INPUT)
		{
			if (IOP.pin_port == CODE_PORTA)
			{
				DDRA &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTB)
			{
				DDRB &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTC)
			{
				DDRC &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTD)
			{
				DDRD &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTE)
			{
				DDRE &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTF)
			{
				DDRF &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTG)
			{
				DDRG &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTH)
			{
				DDRH &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTJ)
			{
				DDRJ &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTK)
			{
				DDRK &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTL)
			{
				DDRL &= ~1 << IOP.pin_number;
			}
		}
		else if (mode == MODE_OUTPUT)
		{
			if (IOP.pin_port == CODE_PORTA)
			{
				DDRA |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTB)
			{
				DDRB |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTC)
			{
				DDRC |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTD)
			{
				DDRD |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTE)
			{
				DDRE |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTF)
			{
				DDRF |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTG)
			{
				DDRG |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTH)
			{
				DDRH |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTJ)
			{
				DDRJ |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTK)
			{
				DDRK |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTL)
			{
				DDRL |= 1 << IOP.pin_number;
			}
		}
		else if (mode == MODE_INPUT_PULLUP)
		{
			if (IOP.pin_port == CODE_PORTA)
			{
				DDRA &= ~1 << IOP.pin_number;
				PORTA |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTB)
			{
				DDRB &= ~1 << IOP.pin_number;
				PORTB |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTC)
			{
				DDRC &= ~1 << IOP.pin_number;
				PORTC |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTD)
			{
				DDRD &= ~1 << IOP.pin_number;
				PORTD |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTE)
			{
				DDRE &= ~1 << IOP.pin_number;
				PORTE |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTF)
			{
				DDRF &= ~1 << IOP.pin_number;
				PORTF |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTG)
			{
				DDRG &= ~1 << IOP.pin_number;
				PORTG |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTH)
			{
				DDRH &= ~1 << IOP.pin_number;
				PORTH |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTJ)
			{
				DDRJ &= ~1 << IOP.pin_number;
				PORTJ |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTK)
			{
				DDRK &= ~1 << IOP.pin_number;
				PORTK |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTL)
			{
				DDRL &= ~1 << IOP.pin_number;
				PORTL |= 1 << IOP.pin_number;
			}
		}
	}

	inline static constexpr void IOWrite(const uint8_t output)
	{
		if (output == OUTPUT_LOW)
		{
			if (IOP.pin_port == CODE_PORTA)
			{
				PORTA &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTB)
			{
				PORTB &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTC)
			{
				PORTC &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTD)
			{
				PORTD &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTE)
			{
				PORTE &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTF)
			{
				PORTF &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTG)
			{
				PORTG &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTH)
			{
				PORTH &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTJ)
			{
				PORTJ &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTK)
			{
				PORTK &= ~1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTL)
			{
				PORTL &= ~1 << IOP.pin_number;
			}
		}
		else
		{
			if (IOP.pin_port == CODE_PORTA)
			{
				PORTA |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTB)
			{
				PORTB |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTC)
			{
				PORTC |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTD)
			{
				PORTD |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTE)
			{
				PORTE |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTF)
			{
				PORTF |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTG)
			{
				PORTG |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTH)
			{
				PORTH |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTJ)
			{
				PORTJ |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTK)
			{
				PORTK |= 1 << IOP.pin_number;
			}
			else if (IOP.pin_port == CODE_PORTL)
			{
				PORTL |= 1 << IOP.pin_number;
			}
		}
	}

	inline static constexpr void IOToggle()
	{

		if (IOP.pin_port == CODE_PORTA)
		{
			PORTA ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTB)
		{
			PORTB ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTC)
		{
			PORTC ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTD)
		{
			PORTD ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTE)
		{
			PORTE ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTF)
		{
			PORTF ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTG)
		{
			PORTG ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTH)
		{
			PORTH ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTJ)
		{
			PORTJ ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTK)
		{
			PORTK ^= 1 << IOP.pin_number;
		}
		else if (IOP.pin_port == CODE_PORTL)
		{
			PORTL ^= 1 << IOP.pin_number;
		}
	}

	inline static constexpr uint8_t IORead()
	{
		if (IOP.pin_port == CODE_PORTA)
		{
			return PINA;
		}
		else if (IOP.pin_port == CODE_PORTB)
		{
			return PINB;
		}
		else if (IOP.pin_port == CODE_PORTC)
		{
			return PINC;
		}
		else if (IOP.pin_port == CODE_PORTD)
		{
			return PIND;
		}
		else if (IOP.pin_port == CODE_PORTE)
		{
			return PINE;
		}
		else if (IOP.pin_port == CODE_PORTF)
		{
			return PINF;
		}
		else if (IOP.pin_port == CODE_PORTG)
		{
			return PING;
		}
		else if (IOP.pin_port == CODE_PORTH)
		{
			return PINH;
		}
		else if (IOP.pin_port == CODE_PORTJ)
		{
			return PINJ;
		}
		else if (IOP.pin_port == CODE_PORTK)
		{
			return PINK;
		}
		else if (IOP.pin_port == CODE_PORTL)
		{
			return PINL;
		}
	}

	 inline static constexpr uint8_t IOReadBit(const uint8_t &the_bit)
	{
		if (IOP.pin_port == CODE_PORTA)
		{
			return (PINA & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTB)
		{
			return (PINB & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTC)
		{
			return (PINC & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTD)
		{
			return (PIND & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTE)
		{
			return (PINE & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTF)
		{
			return (PINF & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTG)
		{
			return (PING & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTH)
		{
			return (PINH & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTJ)
		{
			return (PINJ & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTK)
		{
			return (PINK & _BV(the_bit));
		}
		else if (IOP.pin_port == CODE_PORTL)
		{
			return (PINL & _BV(the_bit));
		}
	}

};

#endif // __IOFUNCTIONS_H__