#ifndef H_PROCESSING
#define H_PROCESSING

#include <Arduino.h>
#include "Setting.h"
#include "Pins.h"
#include "ConstDefines.h"
#include "AdvancedProcessing.h"
#include "Motors.h"
#include "ExternalInterrupts.h"
#include "Usart.h"
#include "Sending.h"
#include "TempControl.h"
#include "Mouvement.h"
#include "MouvementQueue.h"

uint8_t fProcessing(const char *, char[8], MouvementQueue &);

#endif // H_PROCESSING
