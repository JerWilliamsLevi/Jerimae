// Part of Psyche Capstone Project Spring 2022, class 17A
// Code for remote control IR implementation
// Remote Control Side

// Written by Cecilia Delcamp
// Version 1, Last Update 02/14/2022
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
byte tx_data = 0; // 4 bits replicated
//byte rx_data;

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
  
  IR.listen();
  //if ( IR.isListening() ) {

    // GS_in HIGH when a button is pressed, read encoder bits
    if (GS_in) {
    
      button_flag = true; // a button has been pressed
    
      // Build Data Byte
      // ACK is 1111 1111, 0000 0000 reserved for future use
      bitWrite( tx_data, 0, digitalRead(BIT_0_in) ); // bit 0 of data message
      bitWrite( tx_data, 1, digitalRead(BIT_1_in) ); // bit 1 of data message
      bitWrite( tx_data, 2, digitalRead(BIT_2_in) ); // bit 2 of data message
      bitWrite( tx_data, 3, digitalRead(BIT_3_in) ); // bit 3 of data message

      bitWrite( tx_data, 4, digitalRead(BIT_0_in) ); // bit 0 of data confirm
      bitWrite( tx_data, 5, digitalRead(BIT_1_in) ); // bit 1 of data confirm
      bitWrite( tx_data, 6, digitalRead(BIT_2_in) ); // bit 2 of data confirm
      bitWrite( tx_data, 7, digitalRead(BIT_3_in) ); // bit 3 of data confirm
    }    

    // Once button has been released
    if ( GS_in==0 && button_flag==1 ) {
      // send to IR pin (serial)
      IR.print(tx_data); // send it
      Serial.println("tx data sent, value: " + tx_data);
  
      // Wait while no ACK and timeout_count < TIMEOUT
      // after timeout, if no ACK and resend_count < max, resend
      // If count >= max OR ACK good, set flag and move on

      button_flag = false; // we're done with that button press, good job!
    
  }

  // If IR receive, read byte
  if ( IR.available() ) {
    //read_byte IR.read();
    
  }
    // Bitwise XOR == False for each set, means bits match, declare it good
    //if ( !(bit0^bit4) && !(bit1^bit5) && !(bit2^bit6) && !(bit3^bit7) ) {
      // Send ACK
    //}
    // Else do nothing
  //}
  //}
}
