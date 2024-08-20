
bool gyroIsReady = false;
int16_t accX, accY, accZ, gyroX, gyroY, gyroZ;
int32_t motorPower;

#include "gyro_MPU6050.h"

void setupGyro() {
  setupThisGyro();
}

void loopGyro() {
  motorPower = getMotorPowerWithGyro();

  gyroServoPosition = getHeadServoPositionGyro(motorPower);
}