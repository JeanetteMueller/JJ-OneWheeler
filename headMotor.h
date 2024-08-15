
void setupHeadMotor() {
  headMotorSpeedTarget = 0;
  motor_Head.setSpeed(headMotorSpeedTarget);
}

void loopHeadMotor() {
  if (headMotorTarget >= 1000 && headMotorTarget <= 2000) {
    headMotorSpeedTarget = map(headMotorTarget, 1000, 2000, -maxSpeedValue, maxSpeedValue);

    // Serial.print(F(" headMotorSpeedTarget: "));
    // Serial.println(headMotorSpeedTarget);
  }

  motor_Head.setSpeed(headMotorSpeedTarget);
}