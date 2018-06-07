#ifndef SerialJoystickListener_h
#define SerialJoystickListener_h

#include <Stream.h>
#include <Rover.h>
#include <Joystick.h>

class SerialJoystickListener
{
  public:
    SerialJoystickListener(Stream *stream, Rover *rover, Joystick *joystick);
    void update();
  protected:
    static const int BUFFER_SIZE = 100;
    Stream* _stream = 0;
    Rover* _rover = 0;
    Joystick* _joystick = 0;
};

#endif
