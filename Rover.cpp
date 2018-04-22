#include "Arduino.h"
#include "Engine.h"
#include "Rover.h"

Rover::Rover(Engine *left, Engine *right, int power)
{
  _left = left;
  _right = right;
  _slave = left;
  setPower(power);
}

void Rover::move(float angle)
{ 
  if (angle == 0) {
    _error = abs(_left->getTicks()) - abs(_right->getTicks());
    _slave->setPower(min(255, _slave->getPower() - _error / _errorDivider));
    
    _left->moveClockwise();
    _right->moveCounterclockwise();
  } else if(angle == 1) {
    _left->stop();
    _right->moveClockwise();
  } else if (angle == 2) {
    _error = abs(_left->getTicks()) - abs(_right->getTicks());
    _slave->setPower(min(255, _slave->getPower() - _error / _errorDivider));

    _left->moveCounterclockwise();
    _right->moveClockwise();
  } else if (angle == 3) {
    _left->moveCounterclockwise();
    _right->stop();
  }

  _left->resetTicks();
  _right->resetTicks();
}

void Rover::stop()
{
  _left->stop();
  _right->stop();
}

void Rover::chooseLeftAsSlave()
{
  _slave = _left;
}

void Rover::chooseRightAsSlave()
{
  _slave = _right;
}

void Rover::setPower(int power)
{
  _left->setPower(power);
  _right->setPower(power);
}

void Rover::setErrorDivider(int errorDivider)
{
  _errorDivider = errorDivider;
}

