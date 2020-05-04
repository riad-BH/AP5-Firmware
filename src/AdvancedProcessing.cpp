#include "AdvancedProcessing.h"

#define mq_head mq.mouvements_array[mq.head]

inline void calculateXYAcceleration(MouvementQueue &mq)
{
  if (mq.compareDxDy() && mq.getDx_state(mq.head))
  {
    mq.updateImp_Start();
    mq.updateImp_Finish();
    mq.AccelerationCalculationX();
    mq.setAcceleration_x16(mq.getAcceleration(mq.head) * 16);
    mq.setImp_value_x16(mq.getImp_value(mq.head) * 16);
    mq.setImp_start_x16(mq.getImp_start(mq.head) * 16);
    mq.setImp_size(mq.getImp_start_x16(mq.head), mq.head);
  }
  else if (mq.getDy_state(mq.head))
  {
    mq.updateImp_Start();
    mq.updateImp_Finish();
    mq.AccelerationCalculationY();
    mq.setAcceleration_x16(mq.getAcceleration(mq.head) * 16);
    mq.setImp_value_x16(mq.getImp_value(mq.head) * 16);
    mq.setImp_start_x16(mq.getImp_start(mq.head) * 16);
    mq.setImp_size(mq.getImp_start_x16(mq.head), mq.head);
  }
}

inline void calculateZAcceleration(MouvementQueue &mq)
{
  if (mq.getDz_state(mq.head))
  {
    mq.AccelerationCalculationZ();
    mq.setAcceleration_z_x16(mq.getAcceleration_z(mq.head) * 16);
    mq.setImp_value_z_x16(mq.getImp_value_z(mq.head) * 16);
    mq.setImp_size_z(JERK_Z * 16, mq.head);
  }
}

inline void testAxis(MouvementQueue &mq)
{
  mq.testDx();
  mq.testDy();
  mq.testDz();
  mq.testDe();
}

void advancedProcessing(MouvementQueue &mq)
{

  testAxis(mq);

  mq.mouvementSelection();

  calculateXYAcceleration(mq);
  calculateZAcceleration(mq);

  mq.incrementHead();
  mq.addAvailable_mouvement();
}
/************************************************/