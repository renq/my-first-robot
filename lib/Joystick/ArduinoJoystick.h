#ifndef ArduinoJoystick_h
#define ArduinoJoystick_h

#include "Joystick.h"

class ArduinoJoystick: public Joystick {
  public:
    ArduinoJoystick(int axisX, int axisY);
    ArduinoJoystick(int axisX, int axisY, int deadRadius);
    int getX();
    int getY();
    void update();
  private:
    int _deadRadius = 20;
    int _axisX;
    int _axisY;
};

#endif
