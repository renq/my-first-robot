#ifndef TextJoystick_h
#define TextJoystick_h

#include "Joystick.h"

class TextJoystick: public Joystick {
  public:
    void command(char *command);
};

#endif
