#ifndef Engine_h
#define Engine_h

class Engine
{
  public:
    virtual void moveClockwise() = 0;
    virtual void moveCounterclockwise() = 0;
    virtual void stop() = 0;
    virtual void setPower(int power) = 0;
    virtual int getPower() = 0;
    virtual void resetTicks() = 0;
    virtual long getTicks() = 0;
    virtual void interruptA() = 0;
};

#endif
