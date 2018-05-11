#ifndef PinEngine_h
#define PinEngine_h

#include "Engine.h"

class DummyEngine: public Engine {
  public:
    DummyEngine();
    void moveClockwise();
    void moveCounterclockwise();
    void stop();
    void setPower(int power);
    int getPower();
    void resetTicks();
    long getTicks();
    void interruptA();
    bool isMovingClockwise();
  private:
    int _power = 0;
    bool _clockwise = true;
};

#endif
