#ifndef Joystick_h
#define Joystick_h

#include <stdint.h>

class Joystick
{
  public:
    Joystick();
    Joystick(int16_t deadRadius);

    void setX(int16_t value);
    int getX();

    void setY(int16_t value);
    int getY();

    static const int16_t MIN_VALUE = -512;
    static const int16_t MAX_VALUE = 511;

  protected:
    int16_t _deadRadius = 0;
    int16_t x = 0;
    int16_t y = 0;
};

#endif
