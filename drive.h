
void setupDrive() {
  // set leg motors to zero

  

  motor_L.setSpeed(0);
  motor_R.setSpeed(0);
}



void initLoopDrive() {
  // leftMotorSpeedTarget = 0;
  // rightMotorSpeedTarget = 0;
}

void loopDrive() {
  // uint16_t deadPoint = 5;
  // uint16_t minValue = 1000;
  // uint16_t maxValue = 2000;
  // uint16_t centerPoint = 1500;

  // if (driveValueVertical < centerPoint - deadPoint || driveValueVertical > centerPoint + deadPoint) {
  //   joystickY = map(driveValueVertical, minValue, maxValue, 255, -255);

  //   leftMotorSpeedTarget += joystickY;
  //   rightMotorSpeedTarget += joystickY;
  // }

  // if (driveValueHorizontal < centerPoint - deadPoint || driveValueHorizontal > centerPoint + deadPoint) {
  //   joystickX = map(driveValueHorizontal, minValue, maxValue, 255, -255);

  //   leftMotorSpeedTarget += joystickX;
  //   rightMotorSpeedTarget -= joystickX;
  // }

  // // Make sure motor speeds are within range
  // leftMotorSpeedTarget = constrain(leftMotorSpeedTarget, -255, 255);
  // rightMotorSpeedTarget = constrain(rightMotorSpeedTarget, -255, 255);

  // if (currentMillis - previousMillis_100 >= 100) {
  //   Serial.print(" Left ");
  //   Serial.print(leftMotorSpeedTarget);

  //   Serial.print(" Right ");
  //   Serial.print(rightMotorSpeedTarget);
  // }
}

void updateDriveSpeed() {

  // Serial.print(" Left ");
  // Serial.print(leftMotorSpeedTarget);

  // Serial.print(" Right ");
  // Serial.println(rightMotorSpeedTarget);

  motor_L.setSpeed(leftMotorSpeedTarget);
  motor_R.setSpeed(rightMotorSpeedTarget);
}
