#ifdef PLATFORM_ARDUINO

#include <Ticker.h>
#include <ArduinoEngine.h>
#include <Rover.h>
#include <SerialJoystickListener.h>

#if __AVR_ATmega328P__
  #include "ATmega328P_pins.h"
#elif __AVR_ATmega32U4__
  #include "ATmega32U4_pins.h"
#endif


#if __AVR_ATmega32U4__
  #define JOYSTICK_SERIAL Serial1
  #define DEBUG_SERIAL Serial
#elif __AVR_ATmega328P__
  #include <SoftwareSerial.h>

  SoftwareSerial softSerial(JOYSTICK_WIRE_RX, JOYSTICK_WIRE_TX);
  #define JOYSTICK_SERIAL softSerial
  #define DEBUG_SERIAL Serial
#endif


#ifdef __DEBUG__
 #define DEBUG_PRINT(x) DEBUG_SERIAL.print(x)
 #define DEBUG_PRINTLN(x) DEBUG_SERIAL.println(x)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINTLN(x)
#endif

/*
 * Debug settings
 */
#define DEBUG_TIMER 1000

void encoderLeft();
void encoderRight();
void debug();

ArduinoEngine leftEngine = ArduinoEngine(LEFT_POWER, LEFT_IN1, LEFT_IN2, LEFT_ENC_A, LEFT_ENC_B);
ArduinoEngine rightEngine = ArduinoEngine(RIGHT_POWER, RIGHT_IN1, RIGHT_IN2, RIGHT_ENC_A, RIGHT_ENC_B);
Joystick joystick = Joystick(10);
Rover rover = Rover(&leftEngine, &rightEngine, &joystick);
SerialJoystickListener joystickListener = SerialJoystickListener(&JOYSTICK_SERIAL, &rover, &joystick);
Ticker debugTimer(debug, DEBUG_TIMER);


int main() {
  DEBUG_SERIAL.begin(9600);
  while (!Serial) {
    // wait for connect
  }

  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A), encoderLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), encoderRight, FALLING);

  JOYSTICK_SERIAL.begin(38400);

  rover.chooseLeftAsSlave();
  rover.setPower(255);
  rover.setMinimalEnginePower(40);

  debugTimer.start();

  while (true) {
    joystickListener.update();
    debugTimer.update();
  }
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
