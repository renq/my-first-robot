#ifdef FOR_FUN

/**
 * This file contains a program allowing to test joystick handling
 * in Rover using just Serial monitor.
 */

#include <Arduino.h>
#include <DummyEngine.h>
#include <Rover.h>
#include <TextJoystick.h>
#include <ArduinoJoystick.h>

/*
 * Joystick analog pin settings
 */
#define JOYSTICK_AXIS_X 0
#define JOYSTICK_AXIS_Y 1

DummyEngine leftEngine = DummyEngine();
DummyEngine rightEngine = DummyEngine();
TextJoystick textJoystick = TextJoystick();
ArduinoJoystick arduinoJoystick = ArduinoJoystick(JOYSTICK_AXIS_X, JOYSTICK_AXIS_Y, 20);
Rover rover = Rover(&leftEngine, &rightEngine, &arduinoJoystick);

char inputBuffer[21];


void loopTextJoystick();
void loopArduinoJoystick();

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // loopTextJoystick();
  loopArduinoJoystick();
}

void loopTextJoystick()
{
  if (Serial.available() > 0) {
    int read = Serial.readBytes(inputBuffer, 20);
    inputBuffer[read] = 0;
    textJoystick.command(inputBuffer);

    Serial.print(textJoystick.getX());
    Serial.print(", ");
    Serial.print(textJoystick.getY());
    Serial.print(" ===>> ");

    rover.handleJoystick();

    Serial.print((leftEngine.isMovingClockwise() ? 1 : -1) * leftEngine.getPower());
    Serial.print(", ");
    Serial.println((rightEngine.isMovingClockwise() ? 1 : -1) * rightEngine.getPower());
  }

  delay(30);
}

void loopArduinoJoystick()
{
  arduinoJoystick.update();

  Serial.print(arduinoJoystick.getX());
  Serial.print(", ");
  Serial.print(arduinoJoystick.getY());
  Serial.print(" ====>>> ");

  rover.handleJoystick();
  Serial.print((leftEngine.isMovingClockwise() ? 1 : -1) * leftEngine.getPower());
  Serial.print(", ");
  Serial.println((rightEngine.isMovingClockwise() ? 1 : -1) * rightEngine.getPower());

  delay(333);
}

#endif
