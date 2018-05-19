#ifdef PLATFORM_ARDUINO
#ifdef REAL_ROVER

#include <Arduino.h>
#include <ArduinoEngine.h>
#include <Rover.h>
#include <ArduinoJoystick.h>
#include <Ticker.h>

#define VERSION "v18"

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

/*
 * Joystick pin settings. JOYSTICK_AXIS_X and JOYSTICK_AXIS_Y must be analog
 pins. JOYSTICK_BUTTON is digital pin.
 */
#define JOYSTICK_AXIS_X 0
#define JOYSTICK_AXIS_Y 1
#define JOYSTICK_BUTTON 2

/*
 * Some settings
 */
#define JOYSTICK_REFRESH_RATE 15
#define DEBUG_TIMER 500

void encoderLeft();
void encoderRight();
void updateJoystick();
void debug();

ArduinoEngine leftEngine = ArduinoEngine(LEFT_POWER, LEFT_IN1, LEFT_IN2, LEFT_ENC_A, LEFT_ENC_B);
ArduinoEngine rightEngine = ArduinoEngine(RIGHT_POWER, RIGHT_IN1, RIGHT_IN2, RIGHT_ENC_A, RIGHT_ENC_B);
ArduinoJoystick joystick = ArduinoJoystick(JOYSTICK_AXIS_X, JOYSTICK_AXIS_Y, 10);
Rover rover = Rover(&leftEngine, &rightEngine, &joystick);

Ticker joystickTimer(updateJoystick, JOYSTICK_REFRESH_RATE);
Ticker debugTimer(debug, DEBUG_TIMER);


void setup() {
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A), encoderLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), encoderRight, FALLING);

  pinMode(JOYSTICK_BUTTON, INPUT);

  rover.chooseLeftAsSlave();
  rover.setPower(255);
  rover.setMinimalEnginePower(40);

  joystickTimer.start();
  debugTimer.start();
}

void loop() {
  joystickTimer.update();
  debugTimer.update();
}

void updateJoystick()
{
  joystick.update();
  rover.update();
}

void debug()
{
  // Joystick
  // Serial.print(joystick.getX());
  // Serial.print(",");
  // Serial.print(joystick.getY());
  // Serial.print(" => ");
  // Serial.print(leftEngine.getPower());
  // Serial.print(",");
  // Serial.println(rightEngine.getPower());
  //
  // // Encoders
  // Serial.print("left = ");
  // Serial.print(leftEngine.getTicks());
  // Serial.print(", ");
  // Serial.print("right = ");
  // Serial.println(rightEngine.getTicks());
  // if (analogRead(JOYSTICK_BUTTON) == 0) {
  //   rightEngine.resetTicks();
  //   leftEngine.resetTicks();
  // }
  // Serial.print(digitalRead(LEFT_ENC_A));
  // Serial.print(",");
  // Serial.println(digitalRead(LEFT_ENC_B));
}

void encoderLeft() {
  leftEngine.interruptA();
}

void encoderRight() {
  rightEngine.interruptA();
}

#endif

#endif
