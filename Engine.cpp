#include "Arduino.h"
#include "Engine.h"

Engine::Engine(int powerPin, int in1Pin, int in2Pin, int encAPin, int encBPin)
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

void Engine::moveClockwise()
{
  digitalWrite(_in1Pin, HIGH);
  digitalWrite(_in2Pin, LOW);
}

void Engine::moveCounterclockwise()
{
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, HIGH);
}

void Engine::stop()
{
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
}

void Engine::setPower(unsigned char power)
{
  analogWrite(_powerPin, power);
}

void Engine::resetDistance()
{
  _distance = 0;
}

long Engine::getDistance()
{
  return _distance;
}

void Engine::interruptA()
{
  _distance += digitalRead(_encBPin) == 1 ? 1 : -1;
}

