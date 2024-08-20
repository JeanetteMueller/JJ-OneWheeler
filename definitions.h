#define SERIAL_PORT_SPEED 115200  // Define the port output serial communication speed

// TIME
unsigned long currentMillis;  // time current
unsigned long previousMillis_100 = 0;
unsigned long previousMillis_headServo = 0;
unsigned long previousMillis_gyro = 0;
unsigned long previousMillis_second = 0;

// Head Servo
#include <ESP32Servo.h>
Servo headServo;
uint8_t headServoPin = 12;
int16_t headServoTarget = 1500;
uint16_t minHeadServo = 1;
uint16_t maxHeadServo = 199;
uint16_t servoCenterPosition = ((maxHeadServo - minHeadServo) / 2) + minHeadServo;
int16_t servoPosition = servoCenterPosition;
int16_t gyroServoPosition = 0;
uint16_t gyroHeadMovementAmount = 100; //100 is max
uint16_t joystickHeadMovementAmount = 100; //100 is max

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
#include <CytronMotorDriverEsp32.h>

// Max resolution is 20-bit
// Resolution 65536 (16-bit) for lower frequencies, OK @ 1K
// Resolution  4096 (12-bit) for lower frequencies, OK @ 10K
// Resolution  1024 (10-bit) for higher frequencies, OK @ 50K
// Resolution  256  ( 8-bit)for higher frequencies, OK @ 100K, 200K
// Resolution  128  ( 7-bit) for higher frequencies, OK @ 500K

uint8_t resolution = 10;
uint32_t frequency = 20000;
int32_t maxSpeedValue = (pow(2, resolution) - 1);

CytronMD motor_L(PWM_DIR, 32, 33, 2, frequency, resolution);
CytronMD motor_R(PWM_DIR, 25, 26, 4, frequency, resolution);

int16_t leftMotorSpeedTarget = 0;
int16_t rightMotorSpeedTarget = 0;
uint16_t driveValueHorizontal = 0;
uint16_t driveValueVertical = 0;
int16_t joystickX = 0;
int16_t joystickY = 0;

// Motor Head
CytronMD motor_Head(PWM_DIR, 27, 14, 6, frequency, resolution);
uint16_t headMotorTarget = 0;
int16_t headMotorSpeedTarget = 0;

// LEDs
#include <FastLED.h>
#define lightsPin 4
#define barLightsCount 12
#define eyeLightsCount 3
uint8_t generalLightsBrightness = 255;
#define ledCount (barLightsCount * 4 + eyeLightsCount)
CRGB leds[ledCount];


