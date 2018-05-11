#ifdef PLATFORM_ARDUINO

#include "Arduino.h"
#include "ArduinoJoystick.h"

#ifndef abs
  #define abs(x) ((x)>0?(x):-(x))
#endif

ArduinoJoystick::ArduinoJoystick(int axisX, int axisY)
{
  _axisX = axisX;
  _axisY = axisY;
}

ArduinoJoystick::ArduinoJoystick(int axisX, int axisY, int deadRadius)
{
  _axisX = axisX;
  _axisY = axisY;
  _deadRadius = deadRadius;
}

int ArduinoJoystick::getX()
{
  return abs(Joystick::getX()) < _deadRadius ? 0 : Joystick::getX();
}

int ArduinoJoystick::getY()
{
  return abs(Joystick::getY()) < _deadRadius ? 0 : Joystick::getY();
}

void ArduinoJoystick::update()
{
  setX(analogRead(_axisX) - 512);
  setY(analogRead(_axisY) - 512);
}

#endif
