#include "Engine.h"

#define VERSION "v13"

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

int leftPower = 255;
int rightPower = 255;

unsigned long currentTime;
unsigned long loopTime;

void setup() { 
  Serial.begin(9600);
  currentTime = millis();
  loopTime = currentTime; 

  attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A), encoderLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A), encoderRight, FALLING);
}
 
void loop() {  
  delay(100);
  currentTime = millis();
  handleInput();
//  leftEngine.moveClockwise(); 

  
//  if (currentTime >= loopTime + 5) {  
//    handleLeftEngine();
//    handleRightEngine();
//  }

  loopTime = currentTime;
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
        leftEngine.moveClockwise();
        rightEngine.moveCounterclockwise();
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
        leftEngine.stop();
        rightEngine.stop();
        break;
      case 'x':
        leftEngine.moveCounterclockwise();
        rightEngine.moveClockwise();
        break;
        
      case '0':
        leftEngine.resetDistance();
        rightEngine.resetDistance();
        break;

      case '1':
        Serial.println(leftEngine.getDistance());
        break;
        
      case '2':
        Serial.println(rightEngine.getDistance());
        break;

      // calibrate
      case 'c':
        leftEngine.stop();
        rightEngine.stop();
        
        leftEngine.resetDistance();
        rightEngine.resetDistance();

        leftPower = 255;
        rightPower = 255;
        
        leftEngine.setPower(leftPower);
        rightEngine.setPower(rightPower);
        
        leftEngine.moveClockwise();
        rightEngine.moveClockwise();

        delay(100);
        
        int diff;
        do {
          leftEngine.resetDistance();
          rightEngine.resetDistance();
          delay(333);
          
          Serial.print("Left engine distance: ");
          Serial.println(leftEngine.getDistance());
          Serial.print("Right engine distance: ");
          Serial.println(rightEngine.getDistance());
          diff = rightEngine.getDistance() - leftEngine.getDistance();
          if (diff > 0) {
            rightPower--;
          }
          if (diff < 0) {
            leftPower--;
          }
          
          Serial.print("Set up left power to: ");
          Serial.println(leftPower);
          Serial.print("Set up right power to: ");
          Serial.println(rightPower);
          leftEngine.setPower(leftPower);
          rightEngine.setPower(rightPower);

        } while (abs(diff) > 3);
        
        leftEngine.stop();
        rightEngine.stop();
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

