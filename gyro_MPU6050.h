
// Gyro
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 mpu(0x68);  // <-- use for AD0 high

int16_t targetAngle = -2.4;
uint16_t emergencyStopTiltValue = 4000;


int16_t gyroRate;
float accAngle, gyroAngle, currentAngle, prevAngle = 0, error, prevError = 0, errorSum = 0, sampleTime;
unsigned long lastMicros = 0;

// #define ULONG_MAX 4294967295UL

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

void setupThisGyro() {
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

int32_t getMotorPowerWithGyro() {

  int32_t newMotorPower = 0;

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

  if (accX > emergencyStopTiltValue || accX < -emergencyStopTiltValue) {
    Serial.println("to far tiltet -> motor stop");
    gyroIsReady = false;

  } else if (currentMillis > 3000) {

    unsigned long us = micros();
    unsigned long timediffUS;
    if (us < lastMicros) {
      timediffUS = (ULONG_MAX - lastMicros) + us;
    } else {
      timediffUS = us - lastMicros;
    }
    lastMicros = us;
    sampleTime = timediffUS / 1000000.0;

    if (fabs(accZ) > 0.001) {
      accAngle = atan2(accY, accZ) * RAD_TO_DEG;
    }
    gyroRate = map(gyroX, -32768, 32767, -250, 250);

    gyroAngle = (float)gyroRate * sampleTime;
    currentAngle = 0.9934 * (prevAngle + gyroAngle) + 0.0066 * (accAngle);
    error = currentAngle - targetAngle;
    errorSum = errorSum + error;
    errorSum = constrain(errorSum, -300, 300);
    //calculate output from P, I and D values

    newMotorPower = Kp * (error) + Ki * (errorSum)*sampleTime - Kd * (currentAngle - prevAngle) / sampleTime;

    prevAngle = currentAngle;

    Serial.print("  currentAngle: ");
    Serial.print(currentAngle);

    newMotorPower = constrain(newMotorPower, -255, 255);

    newMotorPower = map(newMotorPower, -255, 255, -maxSpeedValue, maxSpeedValue);

    int16_t minValue = 20;  //value 0-x is not powerfull enough to rotate so this is the minimum value

    if (newMotorPower > 2) {
      newMotorPower = map(newMotorPower, 2, 255, minValue, 255);
    } else if (newMotorPower < -2) {
      newMotorPower = map(newMotorPower, -2, -255, -(minValue), -255);
    } else {
      newMotorPower = 0;
    }

    gyroIsReady = true;

  } else {
    gyroIsReady = false;
  }
  return newMotorPower;

  //Serial.println("Gyro loop end");
}

int16_t getHeadServoPositionGyro(int32_t mp) {
  return map(mp, -maxSpeedValue, maxSpeedValue, -joystickHeadMovementAmount, joystickHeadMovementAmount);
}


