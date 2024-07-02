
#define SERIAL_PORT_SPEED 115200 // Define the port output serial communication speed

// TIME            
unsigned long currentMillis; // time current
unsigned long previousMillis_100 = 0;

//Gyro
MPU6050 mpu;

//Head Servo
uint8_t headServoPin = 3;
int16_t headServoTarget = 1500;


IBusBM IBus;
//values coming from the iBUS RC-Reciever
uint16_t ibusVar00 = 1500;
uint16_t ibusVar01 = 1500;
uint16_t ibusVar02 = 1500;
uint16_t ibusVar03 = 1500;
uint16_t ibusVar04 = 0;
uint16_t ibusVar05 = 0;
uint16_t ibusVar06 = 0;
uint16_t ibusVar07 = 0;
uint16_t ibusVar08 = 0;
uint16_t ibusVar09 = 0;

// Motor Drive
CytronMD motor_L(PWM_DIR, 5, A2);
CytronMD motor_R(PWM_DIR, 6, A3);

int16_t leftMotorSpeedTarget = 0;
int16_t rightMotorSpeedTarget = 0;

uint16_t driveValueHorizontal = 1500;
uint16_t driveValueVertical = 1500;

int16_t joystickX = 0;
int16_t joystickY = 0;