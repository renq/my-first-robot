#include "Joystick.h"

#ifndef abs
  #define abs(x) ((x) > 0 ? x : -x)
#endif

Joystick::Joystick()
{
}

Joystick::Joystick(int16_t deadRadius)
{
  _deadRadius = deadRadius;
}

void Joystick::setX(int16_t value)
{
  x = value;
}

int Joystick::getX()
{
  return abs(x) >= _deadRadius ? x : 0;
}

void Joystick::setY(int16_t value)
{
  y = value;
}

int Joystick::getY()
{
  return abs(y) >= _deadRadius ? y : 0;
}
