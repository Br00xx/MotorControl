//A delay of 1000 Microseconds is Full Reverse
//A delay of 1000 to 1460 Microseconds is Proportional Reverse
//A delay of 1460 to 1540 Microseconds is neutral
//A delay of 1540 to 2000 Microseconds is Proportional Forward
//A delay of 2000 Microseconds is Full Forward

#include <Servo.h>

//PID constants
double kp = 2;
double ki = 5;
double kd = 1;
 
unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double input, output, setPoint;
double cumError, rateError;

int solenoidPin = 1;      //Solenoid that controls the latch

int backLeftPin = 7;      //Back Left Motor pin
int backLeftSpeed = 1460; //Back Left Motor starting speed
Servo backLeftMotor;           //Back Left Motor Servo Object

int frontLeftPin = 6;      //Front Left Motor pin
int frontLeftSpeed = 1460; //Front Left Motor starting speed
Servo frontLeftMotor;           //Front Left Motor Servo Object

int backRightPin = 5;      //Back Right Motor pin
int backRightSpeed = 1460; //Back Right Motor starting speed
Servo backRightMotor;           //Back Right Motor Servo Object

int frontRightPin = 4;      //Front Right Motor pin
int frontRightSpeed = 1460; //Front Right Motor starting speed
Servo frontRightMotor;           //Front Right Motor Servo Object

int Speed = 1460;           //Starting speed for Serial communication

void setup(){
  // Tells each of the servo objects which pin it should output to
  backLeftMotor.attach(backLeftPin);
  frontLeftMotor.attach(frontLeftPin);
  backRightMotor.attach(backRightPin);
  frontRightMotor.attach(frontRightPin);

  //Tells which pin controls the solenoid for the deposition system
  pinMode(solenoidPin, OUTPUT);

  //Set point of encoder to zero degrees
  setPoint = 0;
  
  Serial.begin(115200);
}

void loop()
{
  depositionControl();
  motorControl();
  collectionMotorControl();
}
