#ifndef PinEngine_h
#define PinEngine_h

#include "Engine.h"

class PinEngine: public Engine {
  public:
    PinEngine(int powerPin, int in1Pin, int in2Pin, int encAPin, int encBPin);
    void moveClockwise();
    void moveCounterclockwise();
    void stop();
    void setPower(int power);
    int getPower();
    void resetTicks();
    long getTicks();
    void interruptA();
  private:
    int _powerPin;
    int _power;
    int _in1Pin;
    int _in2Pin;
    int _encAPin;
    int _encBPin;
    volatile long _ticks;
};

#endif
