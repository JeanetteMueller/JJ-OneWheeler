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

  lsm6dsoxSensor.begin();

  // Enable accelerometer and gyroscope, and check success
  if (lsm6dsoxSensor.Enable_X() == LSM6DSOX_OK && lsm6dsoxSensor.Enable_G() == LSM6DSOX_OK) {
    Serial.println("Success enabling accelero and gyro");
  } else {
    Serial.println("Error enabling accelero and gyro");
  }

  // Read ID of device and check that it is correct
  uint8_t id;
  lsm6dsoxSensor.ReadID(&id);
  if (id != LSM6DSOX_ID) {
    Serial.println("Wrong ID for LSM6DSOX sensor. Check that device is plugged");
  } else {
    Serial.println("Receviced correct ID for LSM6DSOX sensor");
  }

  // Set accelerometer scale at +- 2G. Available values are +- 2, 4, 8, 16 G
  lsm6dsoxSensor.Set_X_FS(2);

  // Set gyroscope scale at +- 125 degres per second. Available values are +- 125, 250, 500, 1000, 2000 dps
  lsm6dsoxSensor.Set_G_FS(125);


  // Set Accelerometer sample rate to 208 Hz. Available values are +- 12.0, 26.0, 52.0, 104.0, 208.0, 416.0, 833.0, 1667.0, 3333.0, 6667.0 Hz
  lsm6dsoxSensor.Set_X_ODR(208.0f);


  // Set Gyroscope sample rate to 208 Hz. Available values are +- 12.0, 26.0, 52.0, 104.0, 208.0, 416.0, 833.0, 1667.0, 3333.0, 6667.0 Hz
  lsm6dsoxSensor.Set_G_ODR(208.0f);

}

void loopGyro() {

  if (currentMillis < 5000) {
    return;
  }

  int32_t accelerometer[3];
  int32_t gyroscope[3];

  lsm6dsoxSensor.Get_X_Axes(accelerometer);
  lsm6dsoxSensor.Get_G_Axes(gyroscope);

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
  gyroRate = map(gyroX, -32768, 32767, -1000, 1000);

  gyroAngle = (float)gyroRate * sampleTime;
  currentAngle = 0.9934 * (prevAngle + gyroAngle) + 0.0066 * (accAngle);

  // Serial.print(" acc x: ");
  // Serial.print(accX);
  // Serial.print("    y: ");
  // Serial.print(accY);
  // Serial.print("    z: ");
  // Serial.print(accZ);

  // Serial.print("   gyro x: ");
  // Serial.print(gyroX);
  // Serial.print("    currentAngle: ");
  // Serial.print(currentAngle);

  error = currentAngle - targetAngle;
  errorSum = errorSum + error;
  errorSum = constrain(errorSum, -300, 300);
  //calculate output from P, I and D values

  motorPower = Kp * (error) + Ki * (errorSum)*sampleTime - Kd * (currentAngle - prevAngle) / sampleTime;

  motorPower = constrain(motorPower, -maxSpeedValue, maxSpeedValue);

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

  // Serial.print(".   gyro motorpower  ");
  // Serial.println(motorPower);

  if (accX > 300 || accX < -300) {
    Serial.println("to far tiltet -> motor stop --------------------------");
  } else {
    leftMotorSpeedTarget += motorPower;
    rightMotorSpeedTarget += motorPower;
    gyroServoPosition = map(motorPower, -maxSpeedValue, maxSpeedValue, minHeadServo, maxHeadServo);
  }
  //Serial.println("Gyro loop end");
}
