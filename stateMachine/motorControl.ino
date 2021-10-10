void motorControl(uint8_t xDirR, uint8_t xMagnitudeR, uint8_t yDirR, uint8_t yMagnitudeR)
{
  // This code is used when controlling the drive motors
  if (Serial.available() > 0) 
    if (xDirR == 0) {
      Speed = 1500 + (2*xMagnitudeR);
      leftDriveSpeed = rightDriveSpeed = Speed;
    }
    else if (xDirR == 1) {
      Speed = 1500 - (2*xMagnitudeR);
      leftDriveSpeed = rightDriveSpeed = Speed;
    }
    if (xMagnitudeR == 0) {
      Speed = 1500 + (2*yMagnitudeR);
      if (yDirR == 0) {
        leftDriveSpeed = Speed;
        rightDriveSpeed = 2510 - Speed;
      }
      else if (xMagnitude == 1){
        leftDriveSpeed = Speed;
        rightDriveSpeed = Speed;
      }
    }
  
  //This code creates the PWM signal on each pin based on the speed provided
  analogWrite(leftDrivePin, leftDriveSpeed);           //Back left motor driver code
  analogWrite(rightDrivePin, rightDriveSpeed);          //Front left motor driver code
  }
}
