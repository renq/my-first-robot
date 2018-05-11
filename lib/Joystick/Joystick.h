#ifndef Joystick_h
#define Joystick_h

class Joystick
{
  public:
    void setX(int value);
    int getX();

    void setY(int value);
    int getY();

    static const int MIN_VALUE = -512;
    static const int MAX_VALUE = 511;

  protected:
    int x = 0;
    int y = 0;
};

#endif
