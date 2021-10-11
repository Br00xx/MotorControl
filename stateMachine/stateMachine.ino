//Retrieving all libraries needed
#include <PID_v1.h>
#include <RH_RF69.h>
#include <SPI.h>


//A delay of 1000 Microseconds is Full Reverse
//A delay of 1000 to 1460 Microseconds is Proportional Reverse
//A delay of 1460 to 1540 Microseconds is neutral
//A delay of 1540 to 2000 Microseconds is Proportional Forward
//A delay of 2000 Microseconds is Full Forward

//Setup for Drive System
int Speed = 1500;             

int leftDrivePin = 44;              //Back Left Motor pin
int leftDriveSpeed = Speed;         //Back Left Motor starting speed

int rightDrivePin = 45;             //Back Right Motor pin
int rightDriveSpeed = Speed;        //Back Right Motor starting speed

//Setup for DepositionSystem
int solDepositionPin = 1;           //Solenoid that controls the latch

//Setup for Feedback System
RH_RF69 rf69;                  //Initialise the RFM69HCW library with pin 10 as Chip Select, and pin 2 as data recieved interrupt
uint8_t count = 0;             //Create variable to count

uint8_t xDirR = 0;             //Desired x direction: Left (1) / Right (0) 
uint8_t yDirR = 0;             //Desired y direction: Backwards (1) / Forwards (0)

uint8_t stopStatusR = 0;       //Stop button pressed
uint8_t collectStatusR = 0;    //Collection button pressed
uint8_t depositStatusR = 0;    //Depositing button pressed

uint8_t xMagnitudeR = 0;       //Desired x direction speed
uint8_t yMagnitudeR = 0;       //Desired y direction speed

uint8_t xDirS = 0;             //Actual x direction: Left (1) / Right (0) 
uint8_t yDirS = 0;             //Actual y direction: Backwards (1) / Forwards (0)

uint8_t stopStatusS = 0;       //Stopped
uint8_t collectStatusS = 0;    //Collecting
uint8_t depositStatusS = 0;    //Depositing

uint8_t xMagnitudeS = 0;       //Actual x direction speed
uint8_t yMagnitudeS = 0;       //Actual y direction speed


void setup(){
  // Tells each of the servo objects which pin it should output to
  pinMode(leftDrivePin, OUTPUT);
  pinMode(rightDrivePin, OUTPUT);

  //Tells which pin controls the solenoid for the deposition system
  pinMode(solDepositionPin, OUTPUT);

  //Set point of encoder to zero degrees
  int setPoint = 0;

  //Setup the RFM69HCW
  rf69.init();                           //Start the RFM69HCW module
  rf69.setFrequency(433.4);              //Set the RFM69HCW frequency to 433.3 MHz
  rf69.setTxPower(12, true);             //Set the RFM69HCW output power to +13 dBm, indicate that the moudle is high power capable
  
  //Set the encryption key
  uint8_t key[] = { 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
                    0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A
                  };
  rf69.setEncryptionKey(key);

  //Configure the communication protocol
  rf69.setModemConfig(RH_RF69::GFSK_Rb250Fd250); //GFSK format at 250 kbit/sec
  rf69.setPreambleLength(3);                     //Set a length of 3 bytes

  Serial.begin(115200);
}

void loop()
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
  depositionControl(depositStatusR);
  motorControl(xDirR, xMagnitudeR, yDirR, yMagnitudeR);
  collectionMotorControl(collectStatusR);
}
