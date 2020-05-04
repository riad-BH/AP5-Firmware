#ifndef __INTERVALBINARYSEARCH_H__
#define __INTERVALBINARYSEARCH_H__

#include "Arduino.h"
#include "Sending.h"

class intervalBinarySearch
{
private:

  static uint16_t v1;
  static uint16_t v2;
  static uint32_t FIRST_VALUE;
  static uint32_t LAST_VALUE;
  static uint16_t middle_point;
  static uint32_t return_value;

  friend class BackgroundTasks;

public:

  template <const uint16_t ARRAYSIZE>
  static void search(const uint32_t (&sorted_array)[ARRAYSIZE][2], const uint32_t &value);
};

template <const uint16_t ARRAYSIZE>
void intervalBinarySearch::search(const uint32_t (&sorted_array)[ARRAYSIZE][2], const uint32_t &value)
{
  v1 = 0;
  v2 = ARRAYSIZE;

  middle_point = (v1 + v2) / 2;

  FIRST_VALUE = pgm_read_dword_near((&sorted_array[0][0]));
  LAST_VALUE = pgm_read_dword_near((&sorted_array[ARRAYSIZE - 1][0]));


  if (value < LAST_VALUE)
  {
    return_value = pgm_read_dword_near((&sorted_array[0][1]));
    return;
  }

  else if (value > FIRST_VALUE)
  {
    return_value = pgm_read_dword_near((&sorted_array[ARRAYSIZE - 1][1]));
    return;
  }

  for (uint16_t i = 0; i < ARRAYSIZE; i++)
  {
    if (value == pgm_read_dword_near((&sorted_array[middle_point][0])))
    {
      return_value = pgm_read_dword_near((&sorted_array[middle_point][1]));
      return;
    }
    if (value < pgm_read_dword_near((&sorted_array[middle_point][0])))
    {
      v1 = middle_point;
    }
    else
    {
      v2 = middle_point;
    }
    if (v2 - v1 == 1)
    {
      return_value = pgm_read_dword_near((&sorted_array[v2][1]));
      return;
    }
    middle_point = (v1 + v2) / 2;
  }

  sendLine("not found");
  jumpLine();
  return;
}

#endif // __INTERVALBINARYSEARCH_H__