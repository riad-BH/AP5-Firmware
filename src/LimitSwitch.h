#if !defined(H_LIMIT_SWITCH)
#define H_LIMIT_SWITCH

#include <Arduino.h>
#include "Setting.h"
#include "MouvementQueue.h"
#include "Motors.h"

class LimitSwitchs
{

public:
  static void fLSFowardX(MouvementQueue &mq);
  static void fLSBackwardX(MouvementQueue &mq);

  static void fLSFowardY(MouvementQueue &mq);
  static void fLSBackwardY(MouvementQueue &mq);
};

#endif // H_LIMIT_SWITCH
