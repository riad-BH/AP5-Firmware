#if !defined(H_MouvementQueue)
#define H_MouvementQueue

#include "Arduino.h"
#include "Mouvement.h"
#include "Sending.h"
#include "Setting.h"

/*
#define mq_tail mq.mouvements_array[mq.tail]

#define mq_head mq.mouvements_array[mq.head]
*/

class MouvementQueue
{

private:
  volatile uint8_t available_mouvement = 0;

  uint16_t previous_imp_finish = IMP_START;

public:
  Mouvement mouvements_array[RING_BUFFER_SIZE];

  uint8_t head = 0;

  uint8_t tail = 0;

  inline volatile const uint8_t &getAvailable_mouvement()
  {
    return available_mouvement;
  }

  inline void addAvailable_mouvement()
  {
    available_mouvement++;
  }

  inline void removeAvailable_mouvement()
  {
    available_mouvement--;
  }

  inline void incrementHead()
  {
    head++;
    if (head == RING_BUFFER_SIZE)
    {
      head = 0;
    }
  }

  inline void incrementTail()
  {
    tail++;
    if (tail == RING_BUFFER_SIZE)
    {
      tail = 0;
    }
  }

  void inline setDx(const int32_t &_dx) { mouvements_array[head].dx = _dx; }

  void inline setDy(const int32_t &_dy) { mouvements_array[head].dy = _dy; }

  void inline setDz(const int32_t &_dz) { mouvements_array[head].dz = _dz; }

  void inline setDe(const int32_t &_de) { mouvements_array[head].de = _de; }

  void inline setImp_start(const int16_t &f)
  {
    mouvements_array[head].imp_start = f;
  }

  void inline setImp_start_x16(const int16_t &f)
  {
    mouvements_array[head].imp_start_x16 = f;
  }

  void inline setImp_value(const int16_t &f)
  {
    mouvements_array[head].imp_value = f;
  }

  void inline setImp_value_x16(const int16_t &f)
  {
    mouvements_array[head].imp_value_x16 = f;
  }

  void inline setImp_size(const int16_t &f, uint8_t &mouvement_pointer)
  {
    mouvements_array[mouvement_pointer].imp_size = f;
  }

  void inline setAcceleration(const int16_t &a)
  {
    mouvements_array[head].acceleration = a;
  }

  void inline setAcceleration_x16(const int16_t &a)
  {
    mouvements_array[head].acceleration_x16 = a;
  }

  void inline setImp_value_z(const int16_t &f)
  {
    mouvements_array[head].imp_value_z = f;
  }

  void inline setImp_value_z_x16(const int16_t &f)
  {
    mouvements_array[head].imp_value_z_x16 = f;
  }

  void inline setImp_size_z(const int16_t &f, uint8_t &mouvement_pointer)
  {
    mouvements_array[mouvement_pointer].imp_size_z = f;
  }

  void inline setAcceleration_z(const int16_t &a)
  {
    mouvements_array[head].acceleration_z = a;
  }

  void inline setAcceleration_z_x16(const int16_t &a)
  {
    mouvements_array[head].acceleration_z_x16 = a;
  }

  void inline setAngle(const int16_t &a)
  {
    mouvements_array[head].next_angle = a;
  }

  void inline setDe_state(const uint8_t &_de_state)
  {
    mouvements_array[head].de_state = _de_state;
  }

  void inline setExtruderSpeed(const uint8_t &_exspeed)
  {
    mouvements_array[head].extruder_speed = _exspeed;
  }

  inline void setStep_xy(const int16_t &a, uint8_t &mouvement_pointer)
  {
    mouvements_array[mouvement_pointer].step_xy = a;
  }

  inline void setOver_xy(const int16_t &a, uint8_t &mouvement_pointer)
  {
    mouvements_array[mouvement_pointer].over_xy = a;
  }

  inline void setStep_z(const int16_t &a, uint8_t &mouvement_pointer)
  {
    mouvements_array[mouvement_pointer].step_z = a;
  }

  inline void setStep_e(const int16_t &a, uint8_t &mouvement_pointer)
  {
    mouvements_array[mouvement_pointer].step_e = a;
  }

  /******************************************/
  inline const int32_t &getDx(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dx;
  }

  inline const int32_t &getDy(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dy;
  }

  inline const int32_t &getDz(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dz;
  }

  inline const int32_t &getDe(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].de;
  }

  inline const uint8_t &getDx_state(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dx_state;
  }

  inline const uint8_t &getDy_state(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dy_state;
  }

  inline const uint8_t &getDz_state(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dz_state;
  }

  inline const uint8_t &getDe_state(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].de_state;
  }

  inline uint16_t &getImp_value(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_value;
  }

  inline uint16_t &getImp_value_x16(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_value_x16;
  }

  inline uint16_t &getImp_size(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_size;
  }

  inline uint16_t &getAcceleration(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].acceleration;
  }

  inline uint16_t &getAcceleration_x16(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].acceleration_x16;
  }

  inline uint16_t &getImp_start(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_start;
  }

  inline uint16_t &getImp_start_x16(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_start_x16;
  }

  inline uint8_t &getExtruderSpeed(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].extruder_speed;
  }

  inline uint16_t &getAccelerationDistance(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].acceleration_distance;
  }

  inline uint16_t &getDecelerationDistance(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].deceleration_starting_point;
  }

  inline uint16_t &getAccelerationDistanceZ(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].acceleration_distance_z;
  }

  inline uint16_t &getDecelerationDistanceZ(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].deceleration_distance_z;
  }

  inline bool &getDxDyCompareResult(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].dx_greater_dy;
  }

  inline uint16_t &getAcceleration_z(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].acceleration_z;
  }

  inline uint16_t &getImp_value_z(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_value_z;
  }

  inline uint16_t &getImp_value_z_x16(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_value_z_x16;
  }

  inline uint16_t &getImp_size_z(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].imp_size_z;
  }

  inline uint16_t &getAcceleration_z_x16(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].acceleration_z_x16;
  }

  inline uint16_t &getStep_xy(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].step_xy;
  }

  inline uint16_t &getOver_xy(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].over_xy;
  }

  inline uint16_t &getStep_z(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].step_z;
  }

  inline uint16_t &getStep_e(uint8_t &mouvement_pointer)
  {
    return mouvements_array[mouvement_pointer].step_e;
  }

  void inline flushMouvemetBuffer() { mouvements_array[head].resetValues(); }

  void inline testDx() { mouvements_array[head].testDx(); }

  void inline testDy() { mouvements_array[head].testDy(); }

  void inline testDz() { mouvements_array[head].testDz(); }

  void inline testDe() { mouvements_array[head].testDe(); }

  bool inline compareDxDy() { return mouvements_array[head].compareDxDy(); }

  void inline updateImp_Start()
  {
    mouvements_array[head].imp_start = previous_imp_finish;
  }

  void inline updateImp_Finish()
  {
    int32_t imp = static_cast<int32_t>(mouvements_array[head].next_angle) *
                      ((static_cast<int32_t>(mouvements_array[head].imp_value) -
                        IMP_START) /
                       180.0f) +
                  IMP_START;
    mouvements_array[head].imp_finish = static_cast<uint16_t>(imp);
  }

  void inline AccelerationCalculationX()
  {
    mouvements_array[head].calculateAccelerationXaxis(previous_imp_finish);
  }

  void inline AccelerationCalculationY()
  {
    mouvements_array[head].calculateAccelerationYaxis(previous_imp_finish);
  }

  void inline AccelerationCalculationZ()
  {
    mouvements_array[head].calculateAccelerationZaxis();
  }

  void inline mouvementSelection()
  {
    mouvements_array[head].mouvementSelection();
  }
};
#endif // H_MouvementQueue
