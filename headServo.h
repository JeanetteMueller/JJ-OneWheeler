
void setupHeadServo() {

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	// ESP32PWM::allocateTimer(2);
	// ESP32PWM::allocateTimer(3);
	headServo.setPeriodHertz(50);    // standard 50 hz servo
  headServo.attach(headServoPin, 500, 2500);
}

void loopHeadServo() {

  servoPosition = servoCenterPosition;

  servoPosition += gyroServoPosition;

  if (headServoTarget >= 1000 && headServoTarget <= 2000) {
    servoPosition += map(headServoTarget, 1000, 2000, joystickHeadMovementAmount, -joystickHeadMovementAmount);
  }

  servoPosition = constrain(servoPosition, minHeadServo, maxHeadServo);

  // Serial.print(F(" headServoTarget: "));
  // Serial.print(headServoTarget);
  // Serial.print(F("     gyroServoPosition: "));
  // Serial.print(gyroServoPosition);
  // Serial.print(F("     Head Servo: "));
  // Serial.println(servoPosition);

  headServo.write(servoPosition);
}
