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

void DummyEngine::setPower(uint8_t power)
{
  _power = power;
}

uint8_t DummyEngine::getPower()
{
  return _power;
}

void DummyEngine::resetTicks()
{
}

int32_t DummyEngine::getTicks()
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
