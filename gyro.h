#include "Arduino.h"

int16_t accX, accY, accZ, gyroX;
int32_t motorPower;
int16_t gyroRate;
float accAngle, gyroAngle, currentAngle, prevAngle = 0, error, prevError = 0, errorSum = 0;
int16_t count = 0;

float sampleTime;
unsigned long lastMicros = 0;

#define ULONG_MAX 4294967295UL

/*
1. Set Ki and Kd to zero and gradually increase Kp so that the robot starts to oscillate about the zero position.
2. Increase Ki so that the response of the robot is faster when it is out of balance. Ki should be large enough so that the angle of inclination does not increase. The robot should come back to zero position if it is inclined.
3. Increase Kd so as to reduce the oscillations. The overshoots should also be reduced by now.
4. Repeat the above steps by fine tuning each parameter to achieve the best result.
*/

// #define Kp 8 //1.5
// #define Kd 0
// #define Ki 1.5 // 5.0

#define Kp 5.0  //1.5
#define Kd 0
#define Ki 0.02  // 5.0

void setupGyro() {

  mpu.initialize();

  //-3970	-3783	1632	121	88	38
  //-4007	-3645	1553	123	84	36

  mpu.setXAccelOffset(-4007);
  mpu.setYAccelOffset(-3645);
  mpu.setZAccelOffset(1553);
  mpu.setXGyroOffset(123);
  mpu.setYGyroOffset(84);
  mpu.setZGyroOffset(36);
}

void loopGyro() {

  unsigned long us = micros();
  unsigned long timediffUS;
  if (us < lastMicros) {
    timediffUS = (ULONG_MAX - lastMicros) + us;
  } else {
    timediffUS = us - lastMicros;
  }
  lastMicros = us;
  sampleTime = timediffUS / 1000000.0;

  accX = mpu.getAccelerationX();
  accY = mpu.getAccelerationY();
  accZ = mpu.getAccelerationZ();

  gyroX = mpu.getRotationX();

  // Serial.print("acc x: ");
  // Serial.print(accX);
  // Serial.print("    y: ");
  // Serial.print(accY);
  // Serial.print("    z: ");
  // Serial.print(accZ);
  // Serial.println("");

  if (fabs(accZ) > 0.001) {
    accAngle = atan2(accY, accZ) * RAD_TO_DEG;
  }
  gyroRate = map(gyroX, -32768, 32767, -1000, 1000);

  gyroAngle = (float)gyroRate * sampleTime;
  currentAngle = 0.9934 * (prevAngle + gyroAngle) + 0.0066 * (accAngle);
  error = currentAngle - targetAngle;
  errorSum = errorSum + error;
  errorSum = constrain(errorSum, -300, 300);
  //calculate output from P, I and D values

  motorPower = Kp * (error) + Ki * (errorSum)*sampleTime - Kd * (currentAngle - prevAngle) / sampleTime;
  
  motorPower = constrain(motorPower, -maxSpeedValue, maxSpeedValue);

  prevAngle = currentAngle;

  // Serial.print(" motorPower2  ");
  // Serial.print(motorPower);

  // int16_t minValue = 20;  //value 0-x is not powerfull enough to rotate so this is the minimum value
  // if (motorPower > 2) {
  //   motorPower = map(motorPower, 2, maxSpeedValue, minValue, maxSpeedValue);
  // } else if (motorPower < -2) {
  //   motorPower = map(motorPower, -2, -maxSpeedValue, -(minValue), -maxSpeedValue);
  // } else {
  //   motorPower = 0;
  // }

  if (motorPower < 10 && motorPower > -10) {
    motorPower = 0;
  }

  // Serial.print(" motorPower3  ");
  // Serial.print(motorPower);

  if (accX > 4000 || accX < -4000) {
    Serial.println("to far tiltet -> motor stop");
  } else {
    leftMotorSpeedTarget += motorPower;
    rightMotorSpeedTarget += motorPower;
    gyroServoPosition = map(motorPower, -maxSpeedValue, maxSpeedValue, minHeadServo, maxHeadServo);
  }
  //Serial.println("Gyro loop end");
}
