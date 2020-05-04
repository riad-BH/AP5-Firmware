#ifndef __FASTLCD_H__
#define __FASTLCD_H__
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "IOFunctions.h"
#include "Pins.h"

#define LCD_DISPLAY_STATE 0b00001100
#define LCD_CURSOR_STATE 0b00001010
#define LCD_CURSOR_BLINK_STATE 0b00001001

#define LCD_COMMAND_CLEAR 0b0000001

class FastLCD
{
public:
  void inline configure()
  {

    delayMicroseconds(50000);
    PORTC &= ~_BV(PIN_LCD_RS);
    PORTC &= ~_BV(PIN_LCD_E);

    // FROM THE DATASHEET
    sendCommand(0b00110000);
    delayMicroseconds(4500);
    sendCommand(0b00110000);
    delayMicroseconds(150);
    sendCommand(0b00110000);

    sendCommand(0b00111000);

    // 0,0,0,Display command, Display ON, cursor ON, cursor blinking ON

    sendCommand(LCD_DISPLAY_STATE | LCD_CURSOR_STATE);

    sendCommand(LCD_COMMAND_CLEAR);
    delayMicroseconds(2000);

    sendCommand(0b00000110);
  }

  void inline sendData(const uint32_t &temperature_readed)
  {
    itoa(temperature_readed, lcdBuffer, DEC);
    sendChar(lcdBuffer[0]);
    sendChar(lcdBuffer[1]);
    sendChar(lcdBuffer[2]);
    sendChar(lcdBuffer[3]);
  }

  void inline sendData(const uint16_t temperature_readed)
  {
    itoa(temperature_readed, lcdBuffer, DEC);
    sendChar(lcdBuffer[0]);
    sendChar(lcdBuffer[1]);
    sendChar(lcdBuffer[2]);
    sendChar(lcdBuffer[3]);
  }

  void inline sendData(const uint8_t temperature_readed)
  {
    itoa(temperature_readed, lcdBuffer, DEC);
    sendChar(lcdBuffer[0]);
    sendChar(lcdBuffer[1]);
    sendChar(lcdBuffer[2]);
    sendChar(lcdBuffer[3]);
  }

  void inline sendLine(const char *line)
  {
    uint8_t line_size = 255;
    for (uint8_t i = 0; i < 255; i++)
    {
      if (line[i] == '\0')
      {
        line_size = i;
        break;
      }
    }

    if (line_size == 255)
    {
      return;
    }

    PORTC |= _BV(PIN_LCD_RS);

    for (uint8_t i = 0; i < line_size; i++)
    {
      sendChar(line[i]);
    }
  }

  void resetCursor()
  {
    // Sending 1000 0000
    // DDRAM ADRESS = 1AAAAAAA
    sendCommand(0x80);
  }

  char lcdBuffer[4];
  uint8_t data_pins[8] = {0, 1, 2, 3, PIN_LCD_D4, PIN_LCD_D5, PIN_LCD_D6, PIN_LCD_D7};

  void inline sendChar(const uint8_t &value)
  {
    //digitalWrite(31, HIGH);
    //IOPort<IOPIN_LCD_RS>::IOWrite(OUTPUT_HIGH);
    PORTC |= _BV(PIN_LCD_RS);
    // write4bits(value >> 4);
    // write4bits(value);
    write8bits(value);
  }

  void inline sendCommand(const uint8_t &command)
  {
    //digitalWrite(31, LOW);
    // IOPort<IOPIN_LCD_RS>::IOWrite(OUTPUT_LOW);
    PORTC &= ~_BV(PIN_LCD_RS);
    // write4bits(command >> 4);
    // write4bits(command);
    write8bits(command);
  }

  void inline write4bits(const uint8_t &value)
  {

    for (int i = 0; i < 4; i++)
    {
      if (((value >> i) & 0x01))
      {
        PORTA |= _BV(data_pins[i]);
      }
      else
      {
        PORTA &= ~_BV(data_pins[i]);
      }
    }

    sendPulse();
  }

  void static inline write8bits(const uint8_t &value)
  {

    PORTA = value;

    sendPulse();
  }

  void static inline sendPulse()
  {

    //IOPort<IOPIN_LCD_E>::IOWrite(OUTPUT_LOW);
    PORTC &= ~_BV(PIN_LCD_E);

    delayMicroseconds(1);
    // IOPort<IOPIN_LCD_E>::IOWrite(OUTPUT_HIGH);

    PORTC |= _BV(PIN_LCD_E);
    delayMicroseconds(1); // enable pulse must be >450ns

    // IOPort<IOPIN_LCD_E>::IOWrite(OUTPUT_LOW);
    PORTC &= ~_BV(PIN_LCD_E);
    delayMicroseconds(50); // commands need > 37us to settle
  }
};
#endif // __FASTLCD_H__
