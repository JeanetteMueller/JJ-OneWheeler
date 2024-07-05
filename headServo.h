#include "core_esp8266_features.h"
#include <Servo.h>

Servo headServo;

uint16_t servoPosition = 0;
// bool direction = true;
// uint8_t stepSize = 5;

uint16_t minHeadServo = 0;
uint16_t maxHeadServo = 190;

int16_t usedRange = 100;

void setupHeadServo() {
  headServo.attach(headServoPin);
}

void loopHeadServo() {

  if (headServoTarget != 0) {

    if (headServoTarget <= 1500+usedRange && headServoTarget >= 1500-usedRange) {
      servoPosition = map(headServoTarget, 1500-usedRange, 1500+usedRange, maxHeadServo, minHeadServo);
    }else if (headServoTarget > 1500+usedRange) {
      servoPosition = minHeadServo;

    }else if (headServoTarget < 1500-usedRange) {
      servoPosition = maxHeadServo;
    }

    servoPosition = constrain(servoPosition, minHeadServo, maxHeadServo);

    // Serial.print(F(" headServoTarget: "));
    // Serial.print(headServoTarget);

    // Serial.print(F("     Head Servo: "));
    // Serial.println(servoPosition);

    headServo.write(servoPosition);

  } else {
    headServo.write(((maxHeadServo - minHeadServo) / 2) + minHeadServo);
  }
}
// void loopHeadServo_Automation(){

//   if (direction == true){
//     servoPosition = servoPosition + stepSize;
//   }else{
//     servoPosition = servoPosition - stepSize;
//   }

//   if (servoPosition > 180) {
//     direction = false;

//   }else if (servoPosition < 0){
//     direction = true;
//   }

//   // Serial.print(F(" Head Servo: "));
//   // Serial.println(servoPosition);

//   headServo.write(servoPosition);
// }