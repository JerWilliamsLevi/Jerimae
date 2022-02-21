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
const byte GS_in = 4; // from encoder, HIGH if any input HIGH
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
const byte IR_RX_in = 2;    // Arduino Pin for receive, requires change interrupt support
const byte IR_TX_out = 6;   // Arduino Pin for transmit 
const int IR_BAUD = 9600;   // Tx & Rx rate
//const byte RESEND_MAX = 3;   // Max number of times to resend a byte
//const int TIMEOUT = 500;    // Time in milliseconds to wait for an ACK
  
// Set up a software serial instance
SoftwareSerial IR(IR_RX_in, IR_TX_out);

// Variable Declarations
bool button_flag = false; // 1 if a button is depressed, 0 after released
bool ACK_flag = false; // if a valid ACK is received
byte rx_data = 0b00000000; // what's received

byte test_data = 0b11011101; // for testing serial

// counters to know if we need to resend
int resend_count = 0;
int timeout_count = 0;

void setup() {
  // put your setup code here, to run once:
  
  // set up IO pins
  pinMode(GS_in, INPUT);

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
    if (digitalRead(GS_in)==0) {
      button_flag=true;
    }

    // Once button has been released
    if ( digitalRead(GS_in)==1 && button_flag==true ) {

      ACK_flag = false; // so we know to wait on an ACK
      
      // send to IR pin (serial)
      IR.print(test_data); // send it
      Serial.print("tx data sent, value: ");Serial.println(test_data);
  
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

    }

    // If IR receive, read byte
    IR.listen();
    if (IR.isListening()) {
      //Serial.println("IR is listening");
      if ( IR.available() > 0  ) {
        rx_data = IR.read();
        if (rx_data > 0) {
          Serial.print("data received, value: ");Serial.write(rx_data);
          Serial.print("\n");
          if ( bitRead(rx_data, 0)^bitRead(rx_data, 4) &&
               bitRead(rx_data, 1)^bitRead(rx_data, 5) &&
               bitRead(rx_data, 2)^bitRead(rx_data, 6) &&
               bitRead(rx_data, 3)^bitRead(rx_data, 7) ) {

                  Serial.println("data valid");
                  if ( rx_data == 255 ) {
                    Serial.println("data is ACK");
                    ACK_flag = true;
                  } 
                  else if ( rx_data == 0 )
                    Serial.println("data is 0");
                  else {
                    IR.print(ACK);
                    Serial.println("ACK sent");
                  }
                }
            else 
              Serial.println("data invalid");
          }
        }
      }

// Feb 20: Serial communication (over wires) works to the Waveforms program
//  But the Waveforms program seems to encode (maybe ASCII or UTF-8) before
//  sending, so the way I'm determining data validity doesn't work with that
// Next: Test with IR LED / Eye, and test using a second microcontroller
//  so I can check if the receive side of the protocol works

        
        // for the remote side, illuminate a light on remote
        // output to a decoder
        
        // for the main controller side, ? change lights on model ?

  
}
