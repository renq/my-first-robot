#include "Engine.h"
#include "Rover.h"

#ifndef abs
  #define abs(x) ((x)>0?(x):-(x))
#endif

#ifndef min
  #define min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef max
  #define max(a,b) ((a)>(b)?(a):(b))
#endif

Rover::Rover(Engine *left, Engine *right, Joystick *joystick)
{
  _left = left;
  _right = right;
  _slave = left;
  _joystick = joystick;
}

void Rover::handleJoystick()
{
  /*
  * Joystick range X, Y: from -512 to +511
  */
  int left, right;
  int sgnx, sgny;

  left = right = _joystick->getY();
  sgnx = (_joystick->getX() > 0 ? 1 : -1);
  sgny = (_joystick->getY() > 0 ? 1 : -1);

  if (sgnx < 0) {
    left = max(0, left + sgny * _joystick->getX());
  } else {
    right = max(0, right - sgny * _joystick->getX());
  }

  // left i right są z przedziału -512 do 511. Gdy liczby są ujemne - cofamy robota
  // Gdy dodatnie - lecimy do przodu.
  // Wartości trzeba przemapować na moc silnika, np. left=right=512 to moc silnika 255.
  //

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
