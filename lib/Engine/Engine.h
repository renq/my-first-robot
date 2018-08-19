#ifndef Engine_h
#define Engine_h

#include <stdint.h>

class Engine
{
  public:
    virtual void moveClockwise() = 0;
    virtual void moveCounterclockwise() = 0;
    virtual void stop() = 0;
    virtual void setPower(uint8_t power) = 0;
    virtual uint8_t getPower() = 0;
    virtual void resetTicks() = 0;
    virtual int32_t getTicks() = 0;
    virtual void interruptA() = 0;

    static const uint8_t MAX_VALUE = 255;
};

#endif
