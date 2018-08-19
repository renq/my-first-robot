#ifdef PLATFORM_ARDUINO

#include "Arduino.h"
#include "ArduinoEngine.h"

ArduinoEngine::ArduinoEngine(uint8_t powerPin, uint8_t in1Pin, uint8_t in2Pin, uint8_t encAPin, uint8_t encBPin)
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
  pinMode(_encBPin, INPUT_PULLUP);

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

void ArduinoEngine::setPower(uint8_t power)
{
  _power = power;
  analogWrite(_powerPin, _power);
}

uint8_t ArduinoEngine::getPower()
{
  return _power;
}

void ArduinoEngine::resetTicks()
{
  _ticks = 0;
}

int32_t ArduinoEngine::getTicks()
{
  return _ticks;
}

void ArduinoEngine::interruptA()
{
  _ticks += digitalRead(_encBPin) == 1 ? 1 : -1;
}

#endif
