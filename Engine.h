/*
  Engine.h - Lipescu's engine class
*/
#ifndef Engine_h
#define Engine_h

#include "Arduino.h"

class Engine
{
  public:
    Engine(int powerPin, int in1Pin, int in2Pin, int encAPin, int encBPin);
    void moveClockwise();
    void moveCounterclockwise();
    void stop();
    void setPower(unsigned char power);
    void resetDistance();
    long getDistance();
    void interruptA();
  private:
    int _powerPin;
    int _in1Pin;
    int _in2Pin;
    int _encAPin;
    int _encBPin;
    char _direction;
    long _distance;
};

#endif

