#ifndef UNIT_TEST

#include "DummyEngine.h"

DummyEngine::DummyEngine()
{
}

void DummyEngine::moveClockwise()
{
}

void DummyEngine::moveCounterclockwise()
{
}

void DummyEngine::stop()
{
}

void DummyEngine::setPower(int power)
{
  _power = power;
}

int DummyEngine::getPower()
{
  return _power;
}

void DummyEngine::resetTicks()
{
}

long DummyEngine::getTicks()
{
  return 0;
}

void DummyEngine::interruptA()
{
}

#endif
