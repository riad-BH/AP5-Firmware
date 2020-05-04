#ifndef H_MOTORS
#define H_MOTORS

#include "ArduinoInclude.h"
#include "ConstDefines.h"
#include "MouvementQueue.h"
#include "Pins.h"
#include "Receiving.h"
#include "Sending.h"
#include "Setting.h"
#include "TimerSetting.h"
#include "Flags.h"

class Motors
{
private:
  // Flags for Motor's mouvement ISR
  volatile uint8_t FLAG_over_greater_dx = 0;
  // Flags for Motor's mouvement ISR
  volatile uint8_t FLAG_over_greater_dy = 0;
  // Acceleration factor value : (1 / accelerationFactor) * _acceleration
  volatile uint8_t accelerationFactor = 0;

public:
  void fMoveExtruder(MouvementQueue &mq);

  void fStopExtruder(MouvementQueue &mq);

  void accelerateXY(MouvementQueue &m_q);

  void accelerateZ(MouvementQueue &mq);

  /**********************************************/
  void mouvementSorter(MouvementQueue &mq);

  void moveSteppers(MouvementQueue &mq);

  void setUpX(MouvementQueue &mq);
  void setUpY(MouvementQueue &mq);

  void setUpZ(MouvementQueue &mq);
  void setUpE(MouvementQueue &mq);

  void moveX(MouvementQueue &mq);
  void moveY(MouvementQueue &mq);
  void moveXY(MouvementQueue &mq);

  void moveXE(MouvementQueue &mq);
  void moveYE(MouvementQueue &mq);
  void moveXYE(MouvementQueue &mq);

  void moveZ(MouvementQueue &mq);
  void moveE(MouvementQueue &mq);
};
#endif // H_MOTORS
