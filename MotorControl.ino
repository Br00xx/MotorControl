//Joseph Schroed | FRC RI3D "Full Moon Robotics"

//A delay of 1000 Microseconds is Full Reverse
//A delay of 1000 to 1460 Microseconds is Proportional Reverse
//A delay of 1460 to 1540 Microseconds is neutral
//A delay of 1540 to 2000 Microseconds is Proportional Forward
//A delay of 2000 Microseconds is Full Forward

#include <Servo.h>

int Speed = 1460;           //Starting speed for Serial communication

int leftPin = 7;      //Back Left Motor pin
int leftSpeed = Speed; //Back Left Motor starting speed
Servo leftMotor;           //Back Left Motor Servo Object

int rightPin = 5;      //Back Right Motor pin
int rightSpeed = Speed; //Back Right Motor starting speed
Servo rightMotor;           //Back Right Motor Servo Object


void setup()
{
  // Tells each of the servo objects which pin it should output to
  leftMotor.attach(leftPin);
  rightMotor.attach(rightPin);

  Serial.begin(115200);
}

void loop()
{
  // This code is used when controlling using serial

  // FORMAT Example: fr 2000
  // FORMAT Example: a 1500

  // If you send the character "a" then all the motors will run at the provided speed
  // fr -> front right
  // fl -> front left
  // br -> back right
  // bl -> back left
  if (Serial.available() > 0) {
    char fb = Serial.read();
    if (fb == 'a') {
      Speed = Serial.parseInt();
      leftSpeed = rightSpeed = Speed;
    }
    else {
      char lr = Serial.read();
      Speed = Serial.parseInt();
      if (fb == 'b') {
        if (lr == 'l') {
          leftSpeed = Speed;
        }
        else {
          rightSpeed = Speed;
        }
      }
      else {
        if (lr == 'l') {
          leftSpeed = Speed;
        }
        else {
          rightSpeed = Speed;
        }
      }
    }
    Serial.println(Speed);
  }
  
  //This code creates the PWM signal on each pin based on the speed provided
  leftMotor.writeMicroseconds(leftSpeed);           //Back left motor driver code

  rightMotor.writeMicroseconds(rightSpeed);          //Front left motor driver code

}
