#ifdef PLATFORM_ARDUINO

#include "Arduino.h"
#include "ArduinoEngine.h"

ArduinoEngine::ArduinoEngine(int powerPin, int in1Pin, int in2Pin, int encAPin, int encBPin)
{
  _powerPin = powerPin;
  _in1Pin = in1Pin;
  _in2Pin = in2Pin;
  _encAPin = encAPin;
  _encBPin = encBPin;


  pinMode(_powerPin, OUTPUT);
  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);
  pinMode(_encAPin, INPUT_PULLUP);
  pinMode(_encBPin, INPUT);

  stop();
  setPower(255);
}

void ArduinoEngine::moveClockwise()
{
  digitalWrite(_in1Pin, HIGH);
  digitalWrite(_in2Pin, LOW);
}

void ArduinoEngine::moveCounterclockwise()
{
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, HIGH);
}

void ArduinoEngine::stop()
{
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
}

void ArduinoEngine::setPower(int power)
{
  _power = power;
  analogWrite(_powerPin, _power);
}

int ArduinoEngine::getPower()
{
  return _power;
}

void ArduinoEngine::resetTicks()
{
  _ticks = 0;
}

long ArduinoEngine::getTicks()
{
  return _ticks;
}

void ArduinoEngine::interruptA()
{
  _ticks += digitalRead(_encBPin) == 1 ? 1 : -1;
}

#endif
