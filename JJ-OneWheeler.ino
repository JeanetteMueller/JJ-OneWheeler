
#include "Arduino.h"

#include "Wire.h"
#include "math.h"

#include "definitions.h"
#include "functions.h"
#include "input.h"
#include "headServo.h"
#include "headMotor.h"
#include "gyro.h"
#include "lights.h"
#include "debug.h"
#include "drive.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_PORT_SPEED);  //Used only for debugging on arduino serial monitor
  Serial.println("JJ Arduino Code! v1.0");

  writeCPUFreq();
  delay(2000);

  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();

  setupInput();
  setupGyro();
  setupDrive();
  setupHeadServo();
  setupHeadMotor();
  setupLights();
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

  if (currentMillis < previousMillis_second) {
    previousMillis_second = 0;
  }

  loopInput();

  if (currentMillis - previousMillis_gyro >= 2) {
    previousMillis_gyro = currentMillis;

    initLoopDrive();
    loopDrive();
    loopGyro();
    updateDriveSpeed();
  }
  
  

  loopHeadMotor();

  if (currentMillis - previousMillis_headServo >= 20) {
    previousMillis_headServo = currentMillis;

    loopHeadServo();
  }

  if (currentMillis - previousMillis_100 >= 100) {
    previousMillis_100 = currentMillis;

    loopLights();
  }

if (currentMillis - previousMillis_second >= 1000) {
    previousMillis_second = currentMillis;

    // debug();

    // Serial.print("-------------------------- loop end at ");
    // Serial.println(currentMillis / 1000);
  }

  // Serial.println("loop end--------------------------");

  // unsigned long endTime = millis();
  // if (endTime > currentMillis+4) {
  //   Serial.print(" WARN !!!!!!!!!!!!!!!!!!!!!!!!!! ");
  //   Serial.print(endTime - currentMillis);
  //   Serial.println("");
  // }
  Serial.println("");
}
