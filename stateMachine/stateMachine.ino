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

int Speed = 1460;           //Starting speed for Serial communication

//WHICH PINS ARE BEING USED????
int leftPin = 7;      //Back Left Motor pin
int leftSpeed = Speed; //Back Left Motor starting speed
Servo leftMotor;           //Back Left Motor Servo Object

int rightPin = 5;      //Back Right Motor pin
int rightSpeed = Speed; //Back Right Motor starting speed
Servo rightMotor;           //Back Right Motor Servo Object


void setup(){
  // Tells each of the servo objects which pin it should output to
  leftMotor.attach(leftPin);
  rightMotor.attach(rightPin);

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
