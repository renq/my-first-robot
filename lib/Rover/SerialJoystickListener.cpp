#include <SerialJoystickListener.h>
#include <Stream.h>
#include <Rover.h>
#include <Joystick.h>
#include <Arduino.h>

SerialJoystickListener::SerialJoystickListener(
  Stream *stream,
  Rover *rover,
  Joystick *joystick
) {
  _stream = stream;
  _rover = rover;
  _joystick = joystick;
}

void SerialJoystickListener::update()
{
  if (_stream->available() > 5) {
    char buffer[SerialJoystickListener::BUFFER_SIZE];
    char command;
    int16_t value;
    int16_t oldX = _joystick->getX();
    int16_t oldY = _joystick->getY();
    int16_t newX, newY;

    _stream->readBytesUntil(0x0A, buffer, 100);
    sscanf(buffer, "%c%d\n", &command, &value);

    switch (command) {
      case 'S':
        newY = map(value, 0, 1024, Joystick::MIN_VALUE, Joystick::MAX_VALUE);
        _joystick->setY(newY);
        break;
      case 'D':
        newX = map(value, 0, 1024, Joystick::MIN_VALUE, Joystick::MAX_VALUE);
        _joystick->setX(newX);
        break;
    }

    if (oldX != newX || oldY != newY) {
      _rover->update();
    }
  }
}
