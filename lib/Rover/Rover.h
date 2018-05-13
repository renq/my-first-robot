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
    void setPower(int power);
    void setErrorDivider(int power);
    void setMinimalEnginePower(int power);
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
    int _error = 0;
    int _errorDivider = 5;
    int _minEnginePower = 0;
};

#endif
