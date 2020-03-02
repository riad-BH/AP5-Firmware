#ifndef H_SENDING
#define H_SENDING
#include <Arduino.h>
#include "Setting.h"

// Function to send data USART_0
void sendData(String);
void sendData(float *);
void sendData(uint8_t *);
void sendData(int8_t *);
void sendData(uint16_t *);
void sendData(int16_t *);
void sendData(uint32_t *);
void sendData(int32_t *);
void sendData(int8_t);
void sendData(int16_t);
void sendData(int32_t);

// Function to send data USART_1
void sendData1(String);
void sendData1(float *);
void sendData1(uint8_t *);
void sendData1(int8_t *);
void sendData1(uint16_t *);
void sendData1(int16_t *);
void sendData1(uint32_t *);
void sendData1(int32_t *);
void sendData1(int32_t);
void sendData1(int16_t);
void sendData1(int8_t);

// Function for the interruption to send data USART_0
void transferData();

// Function for the interruption to send data USART_1
void transferData1();

// Jump line function
#ifdef _PROTEUS
#define jumpLine() sendData("\r")
#else
#define jumpLine() sendData("\n")
#endif

#endif //H_SENDING