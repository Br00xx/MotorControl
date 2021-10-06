void depositionControl(uint8_t depositStatusR)
{
  if (depositStatusR == 1)
  {
    digitalWrite(solDepositionPin, HIGH);      //Switch Solenoid ON
    depositStatusS = 1;
    delay(1000); 
  }
  else {
    digitalWrite(solDepositionPin, LOW);       //Switch Solenoid OFF
    depositStatusS = 0;
    delay(1000); 
  }
}
