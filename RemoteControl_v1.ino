// Part of Psyche Capstone Project Spring 2022, class 17A
// Code for remote control IR implementation
// Remote Control Side

// Written by Cecilia Delcamp
// Version 1, Last Update 02/17/2022
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

// define ACK
const byte ACK = 0b11111111;

// IR serial communication
const byte IR_RX_in = 3;    // Arduino Pin for receive, requires change interrupt support
const byte IR_TX_out = 5;   // Arduino Pin for transmit 
const int IR_BAUD = 9600;   // Tx & Rx rate
//const byte RESEND_MAX = 3;   // Max number of times to resend a byte
const int TIMEOUT = 500;    // Time in milliseconds to wait for an ACK
  
// Set up a software serial instance
SoftwareSerial IR(IR_RX_in, IR_TX_out);

// Variable Declarations
bool button_flag = false; // 1 if a button is depressed, 0 after released
bool ACK_flag = false; // if a valid ACK is received
byte tx_data = 0; // 4 bits duplicated = 1 byte
byte rx_data = 0; // what's received

// counters to know if we need to resend
int resend_count = 0;
int timeout_count = 0;

// to hold received bits for error check
bool bit0 = 0; 
bool bit1 = 0; 
bool bit2 = 0; 
bool bit3 = 0; 

bool bit4 = 0; 
bool bit5 = 0; 
bool bit6 = 0; 
bool bit7 = 0; 


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
Serial.print("test print value = "); Serial.print("3");

}

void loop() {
  // put your main code here, to run repeatedly:


  
  //IR.listen();
  //if ( IR.isListening() ) {
    // GS_in HIGH when a button is pressed, read encoder bits
    if (digitalRead(GS_in)==1) {
    
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
      //Serial.print("data byte: ");Serial.print(tx_data);
    }    

    // Once button has been released
    if ( digitalRead(GS_in)==0 && button_flag==true ) {
      ACK_flag = false; // so we know to wait on an ACK
      
      // send to IR pin (serial)
      IR.write(tx_data); // send it
      Serial.print("tx data sent, value: ");Serial.print(tx_data);

// 2/17 tested - it does think that it is printing, and (apart from shaky connections)
//  ... the values look valid. Haven't yet confirmed that it is in fact sending, or if
//  ... this is the best way or not to use the IR. 
// Next: check that a serial write to an IR results in a data that can be received.

      // Wait while no ACK and timeout_count < TIMEOUT
      // make sure we don't block ourselves waiting on ACKs here
      // means we need to be able to receive & process data while waiting
      // while ( ACK_flag == false && timeout_count < TIMEOUT ) {
      // }
      // after timeout, if no ACK and resend_count < max, resend
      // reset resend
      // If count >= max OR ACK good, set flag and move on
      // if 

      button_flag = false; // we're done with that button press, good job!
    
    
    // If IR receive, read byte
    //if ( IR.available() ) {
    //  rx_data = IR.read();
    //  Serial.println("data received, value: " + rx_data);
    //  bit0 = bitRead(rx_data, 0);
    //  bit1 = bitRead(rx_data, 1);
    //  bit2 = bitRead(rx_data, 2);
    //  bit3 = bitRead(rx_data, 3);
      
    //  bit4 = bitRead(rx_data, 4);
    //  bit5 = bitRead(rx_data, 5);
    //  bit6 = bitRead(rx_data, 6);
    //  bit7 = bitRead(rx_data, 7);
    
    // Bitwise XOR == False for each set, means bits match, declare it good
    //     if ( !(bit0^bit4) && !(bit1^bit5) && !(bit2^bit6) && !(bit3^bit7) ) {
        // If all bits are 1, you have an ACK, set ACK_flag
    //     if ( bit0==1 && bit1==1 && bit2==1 && bit3==1) {
    //      ACK_flag = true;
    //    }
    // If all bits are 0, well, they shouldn't be at this time so do nothing
    //   if ( bit0==0 && bit1==0 && bit2==0 && bit3==0) { } 
    // otherwise, you have received a valid transmission
    // Send ACK
    //   IR.print(ACK);
    //   Serial.println("data valid, ACK sent");
        
    // for the remote side, illuminate a light on remote
    // output to a decoder
        
    // for the main controller side, ? change lights on model ?

    // }
    //else {
    //  Serial.println("invalid data");
    //}
    // Else do nothing
    //}
  }
}
