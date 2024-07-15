
#include "Wire.h"
#include "math.h"

#include "definitions.h"
#include "input.h"
#include "gyro.h"
#include "debug.h"
#include "drive.h"
#include "headServo.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_PORT_SPEED);  //Used only for debugging on arduino serial monitor
  Serial.println("JJ Arduino Code! v1.0");

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  setupInput();
  setupGyro();
  setupDrive();
  setupHeadServo();
}

void loop() {
  // Serial.println("loop start--------------------------");
  currentMillis = millis();

  if (currentMillis < previousMillis_100) {
    previousMillis_100 = 0;
  }

  if (currentMillis < previousMillis_headServo) {
    previousMillis_headServo = 0;
  }

  

  if (currentMillis < previousMillis_gyro) {
    previousMillis_gyro = 0;
  }

  initLoopDrive();

  loopInput();

  loopDrive();

  // debug();

  if (currentMillis - previousMillis_gyro >= 2) {
    previousMillis_gyro = currentMillis;

    loopGyro();
    updateDriveSpeed();
  }

  if (currentMillis - previousMillis_headServo >= 20) {
    previousMillis_headServo = currentMillis;

    loopHeadServo();
  }

  if (currentMillis - previousMillis_100 >= 100) {
    previousMillis_100 = currentMillis;

  }

  // Serial.println("loop end--------------------------");
}
