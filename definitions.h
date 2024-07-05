
#define SERIAL_PORT_SPEED 115200  // Define the port output serial communication speed

// TIME
unsigned long currentMillis;  // time current
unsigned long previousMillis_100 = 0;
unsigned long previousMillis_gyro = 0;

// Gyro
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 mpu(0x68);  // <-- use for AD0 high
int16_t targetAngle = 0;

// Head Servo
uint8_t headServoPin = 13;
int16_t headServoTarget = 0;

// RC Reviever
#include <IBusBM.h>
IBusBM *IBus = new IBusBM();
uint16_t ibusVar00 = 0;
uint16_t ibusVar01 = 0;
uint16_t ibusVar02 = 0;
uint16_t ibusVar03 = 0;
uint16_t ibusVar04 = 0;
uint16_t ibusVar05 = 0;
uint16_t ibusVar06 = 0;
uint16_t ibusVar07 = 0;
uint16_t ibusVar08 = 0;
uint16_t ibusVar09 = 0;

// Motor Drive
#include <CytronMotorDriver.h>
CytronMD motor_L(PWM_DIR, 14, 12);
CytronMD motor_R(PWM_DIR, 0, 16);
int16_t leftMotorSpeedTarget = 0;
int16_t rightMotorSpeedTarget = 0;
uint16_t driveValueHorizontal = 0;
uint16_t driveValueVertical = 0;
int16_t joystickX = 0;
int16_t joystickY = 0;