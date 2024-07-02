

int16_t accY, accZ, gyroX;
volatile int16_t motorPower;
volatile int16_t gyroRate;
volatile float accAngle, gyroAngle, currentAngle, prevAngle = 0, error, prevError = 0, errorSum = 0;
volatile int16_t count = 0;

/*
1. Set Ki and Kd to zero and gradually increase Kp so that the robot starts to oscillate about the zero position.
2. Increase Ki so that the response of the robot is faster when it is out of balance. Ki should be large enough so that the angle of inclination does not increase. The robot should come back to zero position if it is inclined.
3. Increase Kd so as to reduce the oscillations. The overshoots should also be reduced by now.
4. Repeat the above steps by fine tuning each parameter to achieve the best result.
*/

#define Kp 1.5
#define Kd 0
#define Ki 5.0
#define sampleTime 0.005
#define targetAngle 0

void setupGyro() {
  mpu.initialize();

  // mpu.setXAccelOffset(-3972);
  mpu.setYAccelOffset(-3481);
  mpu.setZAccelOffset(1487);
  // mpu.setXGyroOffset(124);
  mpu.setYGyroOffset(84);
  // mpu.setZGyroOffset(40);
}

void loopGyro() {
  accY = mpu.getAccelerationY();
  accZ = mpu.getAccelerationZ();
  gyroX = mpu.getRotationY();

  accAngle = atan2(accY, accZ) * RAD_TO_DEG;
  gyroRate = map(gyroX, -32768, 32767, -250, 250);

  gyroAngle = (float)gyroRate * sampleTime;
  currentAngle = 0.9934 * (prevAngle + gyroAngle) + 0.0066 * (accAngle);
  error = currentAngle - targetAngle;
  errorSum = errorSum + error;
  errorSum = constrain(errorSum, -300, 300);
  //calculate output from P, I and D values

  motorPower = Kp * (error) + Ki * (errorSum)*sampleTime - Kd * (currentAngle - prevAngle) / sampleTime;
  motorPower = constrain(motorPower, -255, 255);

  int16_t minValue = 20; //value 0-x is not powerfull enough to rotate so this is the minimum value

  if (motorPower > 10) {
    motorPower = map(motorPower, 10, 255, minValue, 255);
  } else if (motorPower < -10) {
    motorPower = map(motorPower, 10, -255, -(minValue), -255);
  }else{
    motorPower = 0;
  }

  prevAngle = currentAngle;

  leftMotorSpeedTarget = -(motorPower);
  rightMotorSpeedTarget = -(motorPower);
}
