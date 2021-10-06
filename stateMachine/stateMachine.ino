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
int Speed = 1460;             

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

uint8_t stopStatusS = 0;       //Stoped
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
  depositionControl(depositStatusR);
  motorControl(xDirR, xMagnitudeR, yDirR, yMagnitudeR);
  collectionMotorControl(collectStatusR);
}
