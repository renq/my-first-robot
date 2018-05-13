#ifdef PLATFORM_ARDUINO

#include "Arduino.h"
#include "ArduinoJoystick.h"

#ifndef abs
  #define abs(x) ((x) > 0 ? x : -x)
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

void ArduinoJoystick::update()
{
  int x = analogRead(_axisX) - 512;
  int y = analogRead(_axisY) - 512;
  setX(abs(x) >= _deadRadius ? x : 0);
  setY(abs(y) >= _deadRadius ? y : 0);
}

#endif
