#include "DummyEngine.h"

DummyEngine::DummyEngine()
{
}

void DummyEngine::moveClockwise()
{
  _clockwise = true;
}

void DummyEngine::moveCounterclockwise()
{
  _clockwise = false;
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

bool DummyEngine::isMovingClockwise()
{
  return _clockwise;
}
