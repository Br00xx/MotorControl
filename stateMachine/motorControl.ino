void motorControl(uint8_t xDirR, uint8_t xMagnitudeR, uint8_t yDirR, uint8_t yMagnitudeR)
{
  // This code is used when controlling the drive motors
  if (Serial.available() > 0) {
    char instructions = Serial.read();
    if (instructions == 'a') {
      Speed = Serial.parseInt();
      leftDriveSpeed = rightDriveSpeed = Speed;
    }
    else {
      char lr = Serial.read();
      Speed = Serial.parseInt();
      if (instructions == 'b') {
        if (lr == 'l') {
          leftDriveSpeed = Speed;
        }
        else {
          rightDriveSpeed = Speed;
        }
      }
      else {
        if (lr == 'l') {
          leftDriveSpeed = Speed;
        }
        else {
          rightDriveSpeed = Speed;
        }
      }
    }
  
  //This code creates the PWM signal on each pin based on the speed provided
  analogWrite(leftDrivePin, leftDriveSpeed);           //Back left motor driver code
  analogWrite(rightDrivePin, rightDriveSpeed);          //Front left motor driver code
  }
}
