
// Gyro
#include "ISM330DHCXSensor.h"
ISM330DHCXSensor gyro = ISM330DHCXSensor(&Wire, ISM330DHCX_I2C_ADD_L);

int16_t targetAngle = 21.0;
uint16_t emergencyStopTiltValue = 300;


void setupThisGyro() {

  gyro.begin();

  gyro.ACC_Enable();
  gyro.GYRO_Enable();
}

int32_t getMotorPowerWithGyro() {

  int32_t newMotorPower = 0;

  int32_t accelerometer[3];
  int32_t gyroscope[3];

  gyro.ACC_GetAxes(accelerometer);
  gyro.GYRO_GetAxes(gyroscope);

  accX = accelerometer[0];
  accY = accelerometer[1];
  accZ = accelerometer[2];

  gyroX = gyroscope[0];

  if (accX > emergencyStopTiltValue || accX < -emergencyStopTiltValue) {
    Serial.println("to far tiltet -> motor stop");
    gyroIsReady = false;

  } else if (currentMillis > 3000) {


    //gyro code here

    newMotorPower = constrain(newMotorPower, -maxSpeedValue, maxSpeedValue);

  } else {
    gyroIsReady = false;
  }
  return newMotorPower;
}

int16_t getHeadServoPositionGyro(int32_t mp) {
  return map(mp, -maxSpeedValue, maxSpeedValue, -gyroHeadMovementAmount, gyroHeadMovementAmount);
}