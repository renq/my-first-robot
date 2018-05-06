#ifndef TextJoystick_h
#define TextJoystick_h

#include "Joystick.h"

class TextJoystick: public Joystick {
  public:
    int getX();
    int getY();

    void command(char *command);

  private:
    int x = 0;
    int y = 0;
};

#endif
