#include "Arduino.h"

int16_t accX, accY, accZ, gyroX;
int32_t motorPower;
int16_t gyroRate;
float accAngle, gyroAngle, currentAngle, prevAngle = 0, error, prevError = 0, errorSum = 0;
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

#define Kp 1.5  //1.5
#define Kd 0.0
#define Ki 0.02  // 5.0

void setupGyro() {

  gyro.begin();

  gyro.ACC_Enable();
  gyro.GYRO_Enable();

  // // Enable accelerometer and gyroscope, and check success
  // if (gyro.ACC_Enable() == ISM330DHCX_OK && gyro.GYRO_Enable() == LSM6DSOX_OK) {
  //   Serial.println("Success enabling accelero and gyro");
  // } else {
  //   Serial.println("Error enabling accelero and gyro");
  // }

  // // Read ID of device and check that it is correct
  // uint8_t id;
  // gyro.ReadID(&id);
  // if (id != LSM6DSOX_ID) {
  //   Serial.println("Wrong ID for LSM6DSOX sensor. Check that device is plugged");
  // } else {
  //   Serial.println("Receviced correct ID for LSM6DSOX sensor");
  // }
}

void loopGyro() {

  int32_t accelerometer[3];
  int32_t gyroscope[3];

  gyro.ACC_GetAxes(accelerometer);
  gyro.GYRO_GetAxes(gyroscope);

  accX = accelerometer[0];
  accY = accelerometer[1];
  accZ = accelerometer[2];

  gyroX = gyroscope[0];

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

  Serial.print(" acc x: ");
  Serial.print(accX);
  Serial.print("    y: ");
  Serial.print(accY);
  Serial.print("    z: ");
  Serial.print(accZ);

  Serial.print("   gyro x: ");
  Serial.print(gyroX);
  Serial.print("    currentAngle: ");
  Serial.print(currentAngle);

  error = currentAngle - targetAngle;
  errorSum = errorSum + error;
  Serial.print("       errorSum: ");
  Serial.print(errorSum);

  errorSum = constrain(errorSum, -300, 300);
  //calculate output from P, I and D values

  motorPower = Kp * (error) + Ki * (errorSum) * sampleTime - Kd * (currentAngle - prevAngle) / sampleTime;
  Serial.print("       motorPower: ");
  Serial.print(motorPower);

  motorPower = map(motorPower, -255, 255, -800, 800);
  motorPower = constrain(motorPower, -maxSpeedValue, maxSpeedValue);

  Serial.print(" > ");
  Serial.print(motorPower);

  prevAngle = currentAngle;

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

  if (accX > 200 || accX < -200) {
    Serial.println("to far tiltet -> motor stop --------------------------");
    motorPower = 0;
  } else {

    if (currentMillis > 7000) {
      gyroIsReady = true;
      
      // gyroServoPosition = map(motorPower, -maxSpeedValue, maxSpeedValue, -joystickHeadMovementAmount, joystickHeadMovementAmount);
    }
  }
  //Serial.println("Gyro loop end");
}
