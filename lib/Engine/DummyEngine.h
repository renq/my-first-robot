#ifndef PinEngine_h
#define PinEngine_h

#include "Engine.h"

class DummyEngine: public Engine {
  public:
    DummyEngine();
    void moveClockwise();
    void moveCounterclockwise();
    void stop();
    void setPower(uint8_t power);
    uint8_t getPower();
    void resetTicks();
    int32_t getTicks();
    void interruptA();
    bool isMovingClockwise();
  private:
    uint8_t _power = 0;
    bool _clockwise = true;
};

#endif
