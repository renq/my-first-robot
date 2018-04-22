/*
  Engine.h - Lipescu's Rover class
*/
#ifndef Rover_h
#define Rover_h

#include "Arduino.h"
#include "Engine.h"

class Rover
{
  public:
    Rover(Engine *left, Engine *right, int power);
    void setPower(int power);
    void setErrorDivider(int power);
    void chooseLeftAsSlave();
    void chooseRightAsSlave();
    void move(float angle);
    void stop();
  private:
    Engine *_left;
    Engine *_right;
    Engine *_slave;
    int _error = 0;
    int _errorDivider = 5;
};

#endif

