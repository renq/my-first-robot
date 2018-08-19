/*
  Engine.h - Lipescu's Rover class
*/
#ifndef Rover_h
#define Rover_h

#include <Engine.h>
#include <Joystick.h>

class Rover
{
  public:
    Rover(Engine *left, Engine *right, Joystick *joystick);
    void setPower(uint8_t power);
    void setErrorDivider(uint8_t power);
    void setMinimalEnginePower(uint8_t power);
    void chooseLeftAsSlave();
    void chooseRightAsSlave();
    void move(float angle);
    void stop();
    void update();
  private:
    Engine *_left;
    Engine *_right;
    Engine *_slave;
    Joystick *_joystick;
    uint8_t _error = 0;
    uint8_t _errorDivider = 5;
    uint8_t _minEnginePower = 0;
};

#endif
