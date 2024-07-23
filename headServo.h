#include "core_esp8266_features.h"

#include <Servo.h>
Servo headServo;


int16_t servoPosition = 0;
int16_t gyroServoPosition = 0;

uint16_t minHeadServo = 1;
uint16_t maxHeadServo = 199;
uint16_t joystickHeadMovementAmount = 60; //100 is max
int16_t usedRange = 300;

void setupHeadServo() {
  headServo.attach(headServoPin, 500, 2500, ((maxHeadServo - minHeadServo) / 2) + minHeadServo );
}

void loopHeadServo() {

  servoPosition = gyroServoPosition;

  if (headServoTarget != 0) {

    if (headServoTarget >= 1000 && headServoTarget <= 2000) {
      servoPosition += map(headServoTarget, 1000, 2000, joystickHeadMovementAmount, -joystickHeadMovementAmount);
    }
  }

  if (servoPosition != 0) {
    servoPosition = constrain(servoPosition, minHeadServo, maxHeadServo);

    // Serial.print(F(" headServoTarget: "));
    // Serial.print(headServoTarget);

    // Serial.print(F("     gyroServoPosition: "));
    // Serial.print(gyroServoPosition);

    // Serial.print(F("     Head Servo: "));
    // Serial.println(servoPosition);

    headServo.write(servoPosition);

  } else {
    headServo.write(((maxHeadServo - minHeadServo) / 2) + minHeadServo);
  }
}