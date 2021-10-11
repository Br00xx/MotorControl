void motorControl(uint8_t xDirR, uint8_t xMagnitudeR, uint8_t yDirR, uint8_t yMagnitudeR)
{
  // This code is used when controlling the drive motors
  if (Serial.available() > 0) {
    if (xDirR == 0) {
      Speed = 1500 + (2*xMagnitudeR);
      leftDriveSpeed = rightDriveSpeed = Speed;
      xDirS = 0;
      xMagnitudeS = xMagnitudeR;
    }
    else if (xDirR == 1) {
      Speed = 1500 - (2*xMagnitudeR);
      leftDriveSpeed = rightDriveSpeed = Speed;
      xDirS = 1;
    }
    if (xMagnitudeR == 0) {
      Speed = 1500 + (2*yMagnitudeR);
      if (yDirR == 0) {
        leftDriveSpeed = Speed;
        rightDriveSpeed = 2510 - Speed;
        yDirS = 0;
      }
      else if (xMagnitudeR == 1){
        leftDriveSpeed = Speed;
        rightDriveSpeed = Speed;
        yDirS = 1;
      }
      xMagnitudeS = xMagnitudeR;
    }
    if (xMagnitudeR == 0 && xMagnitudeR == 0){
      stopStatusS = 0;
    }
    if (stopStatusR = 1){
      Speed = 0;
    }
  
  //This code creates the PWM signal on each pin based on the speed provided
  analogWrite(leftDrivePin, leftDriveSpeed);           //Back left motor driver code
  analogWrite(rightDrivePin, rightDriveSpeed);         //Front left motor driver code
  }
}
