#ifndef ArduinoEngine_h
#define ArduinoEngine_h

#include "Engine.h"

class ArduinoEngine: public Engine {
  public:
    ArduinoEngine(uint8_t powerPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t encAPin, uint8_t encBPin);
    void moveClockwise();
    void moveCounterclockwise();
    void stop();
    void setPower(uint8_t power);
    uint8_t getPower();
    void resetTicks();
    int32_t getTicks();
    void interruptA();
  private:
    uint8_t _powerPin;
    uint8_t _power;
    uint8_t _in1Pin;
    uint8_t _in2Pin;
    uint8_t _encAPin;
    uint8_t _encBPin;
    volatile int32_t _ticks;
};

#endif
