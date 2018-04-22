#include "Engine.h"
#include "Rover.h"

#define VERSION "v15"

#define LEFT_IN1 8
#define LEFT_IN2 9
#define RIGHT_IN1 10
#define RIGHT_IN2 11

#define LEFT_POWER 5
#define RIGHT_POWER 6

#define LEFT_ENC_A 0
#define LEFT_ENC_B 1
#define RIGHT_ENC_A 2
#define RIGHT_ENC_B 3


Engine leftEngine = Engine(LEFT_POWER, LEFT_IN1, LEFT_IN2, LEFT_ENC_A, LEFT_ENC_B);
Engine rightEngine = Engine(RIGHT_POWER, RIGHT_IN1, RIGHT_IN2, RIGHT_ENC_A, RIGHT_ENC_B);
Rover rover = Rover(&leftEngine, &rightEngine, 255);

int leftPower = 255;
int rightPower = 255;

unsigned long currentTime;
unsigned long loopTime;

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
  rover.stop();
  delay(5000);

  for (int i = 0; i < 2000; i+=50) {
    rover.move(0);
    delay(50);
  }
//  handleInput();
//  loopTime = currentTime;
//  delay(2000);
}

void encoderLeft() {
  leftEngine.interruptA();
}

void encoderRight() {
  rightEngine.interruptA();
}

void handleInput() {
  if (Serial.available() > 0) {   
    int input = Serial.read();
    // Serial.println(input);
    
    // leftEngine.setPower(100);
    // rightEngine.setPower(100);

    String powerStr = "";

    switch (input) {
      case 'w':
        rover.move(0);
        Serial.println("forward");
        Serial.println(leftEngine.getPower());
        Serial.println(rightEngine.getPower());
        break;
      case 'a':
        leftEngine.stop();
        rightEngine.moveCounterclockwise();
        break;
      case 'd':
        leftEngine.moveClockwise();
        rightEngine.stop();
        break;
      case 's':
        Serial.println("stop");
        rover.stop();
        break;
      case 'x':
        leftEngine.moveCounterclockwise();
        rightEngine.moveClockwise();
        break;
        
      case '0':
        leftEngine.resetTicks();
        rightEngine.resetTicks();
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
}

