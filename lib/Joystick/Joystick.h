#ifndef Joystick_h
#define Joystick_h

class Joystick
{
  public:
    Joystick();
    Joystick(int deadRadius);

    void setX(int value);
    int getX();

    void setY(int value);
    int getY();

    static const int MIN_VALUE = -512;
    static const int MAX_VALUE = 511;

  protected:
    int _deadRadius = 0;
    int x = 0;
    int y = 0;
};

#endif
