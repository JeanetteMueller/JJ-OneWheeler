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
  Serial.println("JJ Arduino Code! v1.0");

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

  // debug();

  // // if ((micros() - lastMicros) / 1e6 >= 5) {
  // //   lastMicros = micros();

  // //   loopGyro();
  // // }

  // if (currentMillis - previousMillis_gyro >= 1) {
  //   previousMillis_gyro = currentMillis;

    loopGyro();
  // }
  

  loopDrive();
  updateDriveSpeed();

  if (currentMillis - previousMillis_100 >= 100) {
    previousMillis_100 = currentMillis;
    
    loopHeadServo();
  }
}
