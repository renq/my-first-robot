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
  char buffer[SerialJoystickListener::BUFFER_SIZE];
  char command;
  int value;

  if (_stream->available()) {
    _stream->readBytesUntil(0x0A, buffer, SerialJoystickListener::BUFFER_SIZE);
    sscanf(buffer, "%c%d\n", &command, &value);

    switch (command) {
      case 'S':
        _joystick->setY(
          map(value, 0, 1024, Joystick::MIN_VALUE, Joystick::MAX_VALUE)
        );
        break;
      case 'D':
        _joystick->setX(
          map(value, 0, 1024, Joystick::MIN_VALUE, Joystick::MAX_VALUE)
        );
        break;
    }
    _rover->update();
  }
}
