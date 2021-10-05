void feedbackControl()
{
  if (rf69.available())
  {

    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];       //Create a recieved data buffer
    uint8_t len = sizeof(buf);                  //Store the length of the buffer

    if (rf69.recv(buf, &len))                   //If data recieved
    {
      uint8_t parityCheck = 0;                  //Create variable for checking if the parity is correct

      for (uint8_t i = 1; i < 8; i++) {
        if (buf[0] & (0x01 << i))
          parityCheck++;                        //Count how many 1's are in the byte
      }

      if (((parityCheck % 2) && (buf[0] & 0x01)) || (!(parityCheck % 2) && !(buf[0] & 0x01))) { //If valid store the data

        stopStatusR = buf[0] & 0x08;
        collectStatusR = buf[0] & 0x04;
        depositStatusR = buf[0] & 0x02;
        xDirR = buf[0] & 0x10;
        yDirR = buf[0] & 0x20;
        xMagnitudeR = buf[1];
        yMagnitudeR = buf[2];

      }

      count = buf[3];                             //Sync the transmission counts

      uint8_t parityCount = 0;
      uint8_t firstByte = (yDirS << 5) | (xDirS << 4) | (stopStatusS << 3) | (collectStatusS << 2) | (depositStatusS << 1); //Store the first byte

      for (uint8_t i = 1; i < 8; i++) {
        if (firstByte & (0x01 << i))
          parityCount++;                          //Count the number of 1's
      }

      /*
        Send a reply after 20 transmissions
      */
      if (count >= 20) {
        uint8_t data[4] = {0, 0, 0, 0};
        data[0] = firstByte | (parityCount % 2);  //Combine data with parity bit
        data[1] = xMagnitudeS;
        data[2] = yMagnitudeS;
        data[3] = count;
        rf69.send(data, sizeof(data));            //Send the data back
        rf69.waitPacketSent();                    //Wait for data to be sent
        count = 0;
      }
    }
  }
}
