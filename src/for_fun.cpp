#ifdef FOR_FUN

/**
 * This file contains a program allowing to test joystick handling
 * in Rover using just Serial monitor.
 */

#include <Arduino.h>
#include <DummyEngine.h>
#include <Rover.h>
#include <TextJoystick.h>

DummyEngine leftEngine = DummyEngine();
DummyEngine rightEngine = DummyEngine();
TextJoystick joystick = TextJoystick();
Rover rover = Rover(&leftEngine, &rightEngine, &joystick);

char inputBuffer[21];

void setup()
{
  Serial.begin(9600);

  rover.chooseLeftAsSlave();
  rover.setPower(255);
}

void loop()
{
  if (Serial.available() > 0) {
    int read = Serial.readBytes(inputBuffer, 20);
    inputBuffer[read] = 0;
    joystick.command(inputBuffer);

    Serial.print(joystick.getX());
    Serial.print(", ");
    Serial.print(joystick.getY());
    Serial.print(" ===>> ");

    rover.handleJoystick();

    Serial.print((leftEngine.isMovingClockwise() ? 1 : -1) * leftEngine.getPower());
    Serial.print(", ");
    Serial.println((rightEngine.isMovingClockwise() ? 1 : -1) * rightEngine.getPower());
  }

  delay(30);
}

#endif
