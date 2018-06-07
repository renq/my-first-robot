#ifdef PLATFORM_ARDUINO

#include <Arduino.h>
#include <Ticker.h>
#include <ArduinoEngine.h>
#include <Rover.h>
#include <SerialJoystickListener.h>

#ifdef __DEBUG__
 #define DEBUG_PRINT(x) Serial.print(x)
 #define DEBUG_PRINTLN(x) Serial.println(x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif

/**
 * Digital output pins (any digital pin)
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
/* ENC_A must be INT pins (internal interrupt) */
#define LEFT_ENC_A 2
#define RIGHT_ENC_A 3
/* ENC_B is regular digital pin */
#define LEFT_ENC_B 12
#define RIGHT_ENC_B 13

/**
 * Joystick pin settings. Used when joystick is serial device (bluetooth).
 * Serial1 TX/RX pins
 */
#define JOYSTICK_WIRE_RX 0
#define JOYSTICK_WIRE_TX 1
#define JOYSTICK_TIMER 0

/*
 * Debug settings
 */
#define DEBUG_TIMER 500

void encoderLeft();
void encoderRight();
void debug();

ArduinoEngine leftEngine = ArduinoEngine(LEFT_POWER, LEFT_IN1, LEFT_IN2, LEFT_ENC_A, LEFT_ENC_B);
ArduinoEngine rightEngine = ArduinoEngine(RIGHT_POWER, RIGHT_IN1, RIGHT_IN2, RIGHT_ENC_A, RIGHT_ENC_B);
Joystick joystick = Joystick(10);
Rover rover = Rover(&leftEngine, &rightEngine, &joystick);
SerialJoystickListener joystickListener = SerialJoystickListener(&Serial1, &rover, &joystick);

Ticker debugTimer(debug, DEBUG_TIMER);


void setup() {
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A), encoderLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), encoderRight, FALLING);

  Serial1.begin(38400);

  rover.chooseLeftAsSlave();
  rover.setPower(255);
  rover.setMinimalEnginePower(40);

  debugTimer.start();
}

void loop() {
  joystickListener.update();
  debugTimer.update();
}

void encoderLeft() {
  leftEngine.interruptA();
}

void encoderRight() {
  rightEngine.interruptA();
}

void debug() {
  // Joystick
  DEBUG_PRINT(joystick.getX());
  DEBUG_PRINT(",");
  DEBUG_PRINT(joystick.getY());
  DEBUG_PRINT(" => ");
  DEBUG_PRINT(leftEngine.getPower());
  DEBUG_PRINT(",");
  DEBUG_PRINTLN(rightEngine.getPower());

  // Encoders
  DEBUG_PRINT("left = ");
  DEBUG_PRINT(leftEngine.getTicks());
  DEBUG_PRINT(", ");
  DEBUG_PRINT("right = ");
  DEBUG_PRINTLN(rightEngine.getTicks());
  DEBUG_PRINT(digitalRead(LEFT_ENC_A));
  DEBUG_PRINT(",");
  DEBUG_PRINTLN(digitalRead(LEFT_ENC_B));
}

#endif
