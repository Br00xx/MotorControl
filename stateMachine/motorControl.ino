

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
    char instructions = Serial.read();
    if (instructions == 'a') {
      Speed = Serial.parseInt();
      leftSpeed = rightSpeed = Speed;
    }
    else {
      char lr = Serial.read();
      Speed = Serial.parseInt();
      if (instructions == 'b') {
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
  
  //This code creates the PWM signal on each pin based on the speed provided
  analogWrite(leftPin, leftSpeed);           //Back left motor driver code
  analogWrite(rightPin, rightSpeed);          //Front left motor driver code
  }
}
