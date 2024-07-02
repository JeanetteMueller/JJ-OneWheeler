#include "Arduino.h"
#include <IBusBM.h>
#include <CytronMotorDriver.h>

#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "math.h"

#include "definitions.h"
#include "functions.h"
#include "gyro.h"
#include "debug.h"
#include "drive.h"
#include "headServo.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_PORT_SPEED);  //Used only for debugging on arduino serial monitor
  Serial.println(F("JJ Arduino Code! v1.0"));

  // Wire.begin();
  // Wire.setClock(400000);

  IBus.begin(Serial);

  setupGyro();

  setupDrive();

  setupHeadServo();
}

void loop() {

  currentMillis = millis();

  if (currentMillis < previousMillis_100) {
    previousMillis_100 = 0;
  }

  if (currentMillis < previousMillis_gyro) {
    previousMillis_gyro = 0;
  }

  initLoopDrive();

  loadRemoteValues();

  if (currentMillis - previousMillis_gyro >= 1) {
    previousMillis_gyro = currentMillis;

    loopGyro();
  }
  

  loopDrive();
  updateDriveSpeed();

  //debug();

  if (currentMillis - previousMillis_100 >= 100) {
    previousMillis_100 = currentMillis;

    Serial.print(" Left ");
    Serial.print(leftMotorSpeedTarget);

    Serial.print(" Right ");
    Serial.println(rightMotorSpeedTarget);

    loopHeadServo();
  }

}
