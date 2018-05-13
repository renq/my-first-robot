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

#ifndef map
  long map(long x, long in_min, long in_max, long out_min, long out_max)
  {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
#endif

Rover::Rover(Engine *left, Engine *right, Joystick *joystick)
{
  _left = left;
  _right = right;
  _slave = left;
  _joystick = joystick;
}

void Rover::update()
{
  long left, right;
  int sgny;

  left = right = _joystick->getY();
  sgny = (_joystick->getY() > 0 ? 1 : -1);

  left = min(Joystick::MAX_VALUE, max(Joystick::MIN_VALUE, left + sgny * _joystick->getX()));
  right = min(Joystick::MAX_VALUE, max(Joystick::MIN_VALUE, right - sgny * _joystick->getX()));

  // left i right are from range from -512 to 511.
  // When both are neative, rover is going backwards.
  // If they are positive, rover is going forward.

  if (left > 0) {
    _left->setPower(map(left, 0, Joystick::MAX_VALUE, _minEnginePower, Engine::MAX_VALUE));
    _left->moveCounterclockwise();
  } else if (left < 0) {
    _left->setPower(map(left, 0, Joystick::MIN_VALUE, _minEnginePower, Engine::MAX_VALUE));
    _left->moveClockwise();
  } else {
    _left->setPower(0);
  }

  if (right > 0) {
    _right->setPower(map(right, 0, Joystick::MAX_VALUE, _minEnginePower, Engine::MAX_VALUE));
    _right->moveClockwise();
  } else if (right < 0) {
    _right->setPower(map(right, 0, Joystick::MIN_VALUE, _minEnginePower, Engine::MAX_VALUE));
    _right->moveCounterclockwise();
  } else {
    _right->setPower(0);
  }
}

// TO BE REMOVED!
// Error compensation algorithm should be moved to handleJoystick
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
    _right->stop();
    _left->moveCounterclockwise();
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

void Rover::setMinimalEnginePower(int power)
{
  _minEnginePower = power;
}
