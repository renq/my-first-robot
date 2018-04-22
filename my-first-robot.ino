#include "Engine.h"
#include "Rover.h"

#define VERSION "v17"

/**
 * Digital output pins
 */
#define LEFT_IN1 8
#define LEFT_IN2 9
#define RIGHT_IN1 10
#define RIGHT_IN2 11

/**
 * Power pins must be PWM type in order to method analogWrite work)
 * In Leonardo PWM pins are: 3, 5-6, 9-11, 13
 */
#define LEFT_POWER 5
#define RIGHT_POWER 6

/*
 * LEFT_ENC_A and RIGHT_ENC_A must be an INTERRUPT type (in Leonardo INT pins are 0-3 and 7).
 * LEFT_ENC_A and RIGHT_ENC_A could by any digital pins.
 */
#define LEFT_ENC_A 0
#define RIGHT_ENC_A 1
#define LEFT_ENC_B 12
#define RIGHT_ENC_B 13

Engine leftEngine = Engine(LEFT_POWER, LEFT_IN1, LEFT_IN2, LEFT_ENC_A, LEFT_ENC_B);
Engine rightEngine = Engine(RIGHT_POWER, RIGHT_IN1, RIGHT_IN2, RIGHT_ENC_A, RIGHT_ENC_B);
Rover rover = Rover(&leftEngine, &rightEngine, 255);

int leftPower = 255;
int rightPower = 255;

unsigned long currentTime;
unsigned long loopTime;

int inputCommand = 's';

void setup() {
  Serial.begin(115200);
  //  currentTime = millis();
  //  loopTime = currentTime;

  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A), encoderLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), encoderRight, FALLING);
  rover.chooseLeftAsSlave();
}

void loop() {
  //  currentTime = millis();
//  rover.stop();
//  delay(5000);
//
//  for (int i = 0; i < 2000; i += 50) {
//    rover.move(0);
//    delay(50);
//  }
  if (Serial.available() > 0) {
    inputCommand = Serial.read();
  }

  handleInput(inputCommand);
  //  loopTime = currentTime;
  delay(50);
}

void encoderLeft() {
  leftEngine.interruptA();
}

void encoderRight() {
  rightEngine.interruptA();
}

void handleInput(int input) {
  // Serial.println(input);

  // leftEngine.setPower(100);
  // rightEngine.setPower(100);

  String powerStr = "";

  switch (input) {
    case 'w':
      rover.move(0);
      Serial.println(leftEngine.getTicks());
      Serial.println(rightEngine.getTicks());
      Serial.println("forward");
      Serial.println(leftEngine.getPower());
      Serial.println(rightEngine.getPower());
      break;
    case 'a':
      rover.move(3);
      break;
    case 'd':
      rover.move(1);
      break;
    case 's':
      rover.stop();
      break;
    case 'x':
      rover.move(2);
      break;

    case '<':
      powerStr += (char)Serial.read();
      powerStr += (char)Serial.read();
      powerStr += (char)Serial.read();
      leftPower = powerStr.toInt();
      Serial.print("Set up left power to: ");
      Serial.println(leftPower);
      leftEngine.setPower(leftPower);
      break;

    case '>':
      powerStr += (char)Serial.read();
      powerStr += (char)Serial.read();
      powerStr += (char)Serial.read();
      rightPower = powerStr.toInt();
      Serial.print("Set up right power to: ");
      Serial.println(rightPower);
      rightEngine.setPower(rightPower);
      break;

    case 'v':
      Serial.println(VERSION);
      break;
  }
}

