#ifndef H_EXTRUDER
#define H_EXTRUDER
#define fMoveExtruder()                \
  if (_FLAG_extruder)                   \
  {                                    \
    extruderStep++;                    \
    if (extruderStep == extruderSpeed) \
    {                                  \
      PORTA |= (_BV(PIN_E_STEP));      \
      extruderStep = 0;                \
    }                                  \
  }

#define fStopExtruder()          \
  if (_FLAG_extruder)             \
  {                              \
    PORTA &= ~(_BV(PIN_E_STEP)); \
  }

#endif // H_EXTRUDER
