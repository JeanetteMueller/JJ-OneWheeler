
void setupDrive() {

  motor_L.setSpeed(0);
  motor_R.setSpeed(0);
}

void initLoopDrive() {
  leftMotorSpeedTarget = 0;
  rightMotorSpeedTarget = 0;
  joystickX = 0;
  joystickY = 0;
}

void loopDrive() {
  uint16_t deadPoint = 5;
  uint16_t minValue = 1050;
  uint16_t maxValue = 1950;
  uint16_t centerPoint = 1500;

  if (driveValueVertical >= 1000 && driveValueVertical <= 2000) {

    if (driveValueVertical < centerPoint - deadPoint || driveValueVertical > centerPoint + deadPoint) {
      joystickY = map(driveValueVertical, minValue, maxValue, -maxSpeedValue, maxSpeedValue);

      leftMotorSpeedTarget += joystickY;
      rightMotorSpeedTarget += joystickY;
    }
  }
  if (driveValueHorizontal >= 1000 && driveValueHorizontal <= 2000) {
    if (driveValueHorizontal < centerPoint - deadPoint || driveValueHorizontal > centerPoint + deadPoint) {
      joystickX = map(driveValueHorizontal, minValue, maxValue, -maxSpeedValue, maxSpeedValue);

      leftMotorSpeedTarget += joystickX * 0.75;
      rightMotorSpeedTarget -= joystickX * 0.75;
    }
  }
}

void updateDriveSpeed() {

  if (gyroIsReady) {

    // Serial.print("    motorPower: ");
    // Serial.print(motorPower);

    leftMotorSpeedTarget += motorPower;
    rightMotorSpeedTarget += motorPower;
  }

  leftMotorSpeedTarget = constrain(leftMotorSpeedTarget, -maxSpeedValue, maxSpeedValue);
  rightMotorSpeedTarget = constrain(rightMotorSpeedTarget, -maxSpeedValue, maxSpeedValue);

  // Serial.print("      Motors: ");

  // Serial.print("       Left  ");
  // Serial.print(leftMotorSpeedTarget);
  // Serial.print("    Right ");
  // Serial.println(rightMotorSpeedTarget);

  motor_L.setSpeed(leftMotorSpeedTarget);
  motor_R.setSpeed(rightMotorSpeedTarget);
}
