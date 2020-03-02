#ifndef H_ISR
#define H_ISR

// Flag set on if there is an extrusion
extern uint8_t FLAG_extrusion_for_timer;

extern void fLSFowardX();
extern void fLSBackwardX();

extern void fLSFowardY();
extern void fLSBackwardY();

extern void transferData();
extern void transferData1();

extern void fReceiving0();
extern void fReceiving1();

extern void fMoveXYE();
extern void fMoveZ();
// Function to send data
extern void sendData(String);
extern void sendData(float *);
extern void sendData(uint8_t *);
extern void sendData(int8_t *);
extern void sendData(uint16_t *);
extern void sendData(int16_t *);
extern void sendData(uint32_t *);
extern void sendData(int32_t *);

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
ISR(TIMER3_COMPA_vect)
{
    if (FLAG_extrusion_for_timer)
    {
        fMoveE();
    }
    else
    {
        fMoveZ();
    }
}

/******************************************/
ISR(INT0_vect)
{
    fLSFowardX();
    sendData("INT0");
    jumpLine();
}

ISR(INT1_vect)
{
    fLSBackwardX();
    sendData("INT1");
    jumpLine();
}

ISR(INT4_vect)
{
    fLSFowardY();
    sendData("INT4");
    jumpLine();
}

ISR(INT5_vect)
{
    fLSBackwardY();
    sendData("INT5");
    jumpLine();
}

#endif // H_ISR
