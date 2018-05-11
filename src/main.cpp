#ifdef PLATFORM_ARDUINO
#ifdef REAL_ROVER

#include <Arduino.h>
#include <PinEngine.h>
#include <Rover.h>
#include <TextJoystick.h>
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
 * Joystick analog pin settings
 */
#define JOYSTICK_AXIS_X 0;
#define JOYSTICK_AXIS_Y 1;

/*
 * Some settings
 */
#define JOYSTICK_REFRESH_RATE 50
#define BUFFER_SIZE 15

void encoderLeft();
void encoderRight();
void updateJoystick();

PinEngine leftEngine = PinEngine(LEFT_POWER, LEFT_IN1, LEFT_IN2, LEFT_ENC_A, LEFT_ENC_B);
PinEngine rightEngine = PinEngine(RIGHT_POWER, RIGHT_IN1, RIGHT_IN2, RIGHT_ENC_A, RIGHT_ENC_B);
TextJoystick joystick = TextJoystick();
Rover rover = Rover(&leftEngine, &rightEngine, &joystick);

char inputBuffer[BUFFER_SIZE];

Ticker timerJoystick(updateJoystick, JOYSTICK_REFRESH_RATE);


void setup() {
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A), encoderLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), encoderRight, FALLING);

  rover.chooseLeftAsSlave();
  rover.setPower(255);

  timerJoystick.start();
}

void loop() {
  timerJoystick.update();
}

void updateJoystick()
{
  if (Serial.available() > 0) {
    int read = Serial.readBytes(inputBuffer, BUFFER_SIZE);
    inputBuffer[read] = 0;

    joystick.command(inputBuffer);
    rover.handleJoystick();
  }
}

void encoderLeft() {
  leftEngine.interruptA();
}

void encoderRight() {
  rightEngine.interruptA();
}

#endif

#endif
