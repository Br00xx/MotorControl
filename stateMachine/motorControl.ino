void motorControl()
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
      backLeftSpeed = frontLeftSpeed = backRightSpeed = frontRightSpeed = Speed;
    }
    else {
      char lr = Serial.read();
      Speed = Serial.parseInt();
      if (fb == 'b') {
        if (lr == 'l') {
          backLeftSpeed = Speed;
        }
        else {
          backRightSpeed = Speed;
        }
      }
      else {
        if (lr == 'l') {
          frontLeftSpeed = Speed;
        }
        else {
          frontRightSpeed = Speed;
        }
      }
    }
    Serial.println(Speed);
  }
  
  //This code creates the PWM signal on each pin based on the speed provided
  backLeftMotor.writeMicroseconds(backLeftSpeed);           //Back left motor driver code

  frontLeftMotor.writeMicroseconds(frontLeftSpeed);          //Back right motor driver code

  backRightMotor.writeMicroseconds(backRightSpeed);          //Front left motor driver code

  frontRightMotor.writeMicroseconds(frontRightSpeed);         //Front right motor driver code
}
