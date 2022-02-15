// Part of Psyche Capstone Project Spring 2022, class 17A
// Code for remote control IR implementation
// Remote Control Side

// Written by Cecilia Delcamp
// Version 1, Last Update 02/13/2022
// Written for use on an Arduino Pro Mini 3.3 V, 8 MHz board

// Libraries Used:
#include <SoftwareSerial.h> // https://www.arduino.cc/en/Reference/softwareSerial

// Declare Constants and Pin Assignments
// Transmit Side
const byte GS_in = 9; // from encoder, HIGH if any input HIGH
const byte BIT_0_in = 10;    // LSB
const byte BIT_1_in = 11;
const byte BIT_2_in = 12;   
const byte BIT_3_in = 13;   // MSB

// Receive Side
//const byte BIT_0_out = ;    // LSB
//const byte BIT_1_out = ;
//const byte BIT_2_out = ;   
//const byte BIT_3_out = ;   // MSB

// IR serial communication
const byte IR_RX_in = 3;    // Arduino Pin for receive, requires change interrupt support
const byte IR_TX_out = 5;   // Arduino Pin for transmit 
const int IR_BAUD = 9600;   // Tx & Rx rate
//const byte RESEND_MAX = 3;   // Max number of times to resend a byte
//const int TIMEOUT = 500;    // Time in milliseconds to wait for an ACK
  
// Set up a software serial instance
SoftwareSerial IR(IR_RX_in, IR_TX_out);

// Variable Declarations
bool button_flag = false; // 1 if a button is depressed, 0 after released
int tx_frame; // what is transmitted
//int rx_frame;

void setup() {
  // put your setup code here, to run once:
  
  // set up IO pins
  pinMode(GS_in, INPUT);
  pinMode(BIT_0_in, INPUT);
  pinMode(BIT_1_in, INPUT);
  pinMode(BIT_2_in, INPUT);
  pinMode(BIT_3_in, INPUT);
  
  // set up IR Serial 
  pinMode(IR_RX_in, INPUT);
  pinMode(IR_TX_out, OUTPUT);
  IR.begin(IR_BAUD);
    
  // Set up Serial to Computer COM port
  Serial.begin(9600);
  // Serial print (status & troubleshooting)
  Serial.println("End of void setup()");

}

void loop() {
  // put your main code here, to run repeatedly:

  int resend_count = 0;
  int timout_count = 0;

  // GS_in HIGH when a button is pressed, read encoder bits
  if (GS_in) {
    
    button_flag = true; // a button has been pressed
    
    // Build Tx frame
    // ? What format? 2 bytes? (1 bit start, 1 bit ACK flag, 8 bit data, 6 bit filler) ?
    bitWrite( tx_frame, 0, 1 ); // start bit
    bitWrite( tx_frame, 1, 0 ); // ACK=0 means not an ACK

    bitWrite( tx_frame, 2, digitalRead(BIT_0_in) ); // bit 0 of data message
    bitWrite( tx_frame, 3, digitalRead(BIT_1_in) ); // bit 1 of data message
    bitWrite( tx_frame, 4, digitalRead(BIT_2_in) ); // bit 2 of data message
    bitWrite( tx_frame, 5, digitalRead(BIT_3_in) ); // bit 3 of data message

    bitWrite( tx_frame, 6, digitalRead(BIT_0_in) ); // bit 0 of data confirm
    bitWrite( tx_frame, 7, digitalRead(BIT_1_in) ); // bit 1 of data confirm
    bitWrite( tx_frame, 8, digitalRead(BIT_2_in) ); // bit 2 of data confirm
    bitWrite( tx_frame, 9, digitalRead(BIT_3_in) ); // bit 3 of data confirm
    
    bitWrite( tx_frame, 10, 1 ); // padding to 16 bits
    bitWrite( tx_frame, 11, 1 ); // padding to 16 bits
    bitWrite( tx_frame, 12, 1 ); // padding to 16 bits
    bitWrite( tx_frame, 13, 1 ); // padding to 16 bits
    bitWrite( tx_frame, 14, 1 ); // padding to 16 bits
    bitWrite( tx_frame, 15, 1 ); // padding to 16 bits

  }    

  // Once button has been released
  if ( GS_in==0 && button_flag==1 ) {
    // send to IR pin (serial)
    IR.print(tx_frame); // send it
    Serial.println("tx frame sent, value: " + tx_frame);
  
    // Wait while no ACK and timeout_count < TIMEOUT
    // after timeout, if no ACK and resend_count < max, resend
    // If count >= max OR ACK good, set flag and move on

    button_flag = false; // we're done with that button press, good job!
    
  }

  // If IR receive, read byte
  //if ( IR.available() ) {
    //read_byte IR.read();
    
    // If Bitwise AND == 1 for all bits, byte is good
    //if ( (bit0&bit4) && (bit1&bit5) && (bit2&bit6) && (bit3&bit7) ) {
      // Send ACK
    //}
    // Else do nothing
  //}
}
