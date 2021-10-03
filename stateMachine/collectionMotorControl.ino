void collectionMotorControl()
{
  input = analogRead(A0);                //read from rotary encoder connected to A0
  output = computePID(input);
  delay(100);
  analogWrite(3, output);                //control the motor based on PID value
}
 
double computePID(double inp)
{     
        currentTime = millis();                //get current time
        elapsedTime = (double)(currentTime - previousTime);        //compute time elapsed from previous computation
        
        error = setPoint - inp;                                // determine error
        cumError += error * elapsedTime;                // compute integral
        rateError = (error - lastError)/elapsedTime;   // compute derivative
 
        double out = kp*error + ki*cumError + kd*rateError;                //PID output               
 
        lastError = error;                                //remember current error
        previousTime = currentTime;                        //remember current time
 
        return out;                                        //have function return the PID output
}
