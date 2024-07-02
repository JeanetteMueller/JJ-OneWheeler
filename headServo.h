#include <PWMServo.h>
PWMServo headServo;

uint8_t servoPosition = 0;
bool direction = true;
uint8_t stepSize = 5;

void setupHeadServo(){
  headServo.attach(headServoPin);
}

void loopHeadServo(){
  
  servoPosition = map(headServoTarget, 1000, 2000, 0, 180);

  servoPosition = constrain(servoPosition, 0, 180);

  // Serial.print(F(" Head Servo: "));
  // Serial.println(servoPosition);

  headServo.write(servoPosition);

}
void loopHeadServo_Automation(){
  
  if (direction == true){
    servoPosition = servoPosition + stepSize;
  }else{
    servoPosition = servoPosition - stepSize;
  }

  if (servoPosition > 180) {
    direction = false;
    
  }else if (servoPosition < 0){
    direction = true;
  }

  // Serial.print(F(" Head Servo: "));
  // Serial.println(servoPosition);

  headServo.write(servoPosition);
}