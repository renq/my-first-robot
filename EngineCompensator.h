/*
  Engine.h - Lipescu's EngineCompensator class
*/
#ifndef EngineCompensator_h
#define EngineCompensator_h

#include "Arduino.h"
#include "Engine.h"

class EngineCompensator
{
  public:
    EngineCompensator(Engine &left, Engine &right);
    void moveForward();
    void moveBack();
    void stop();
    void rotate(float angle);
  private:
    Engine &_left;
    Engine &_right;
};

#endif

