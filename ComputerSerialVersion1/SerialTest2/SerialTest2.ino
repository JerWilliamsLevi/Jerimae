// Part of Psyche Capstone Project Spring 2022, class 17A
// Code for Testing Serial from computer

// Written by Cecilia Delcamp
// Version 1, Last Update 03/09/2022
// Written for use on an Elegoo Mega 2560 R3
// Uses the additional serial ports instead of SoftwareSerial

// Libraries Used:
//#include <SoftwareSerial.h> // https://www.arduino.cc/en/Reference/softwareSerial

// Declare Constants and Pin Assignments

// Software Serial communication
//const byte SW_RX_in = 2;    // Arduino Pin for receive, requires change interrupt support
//const byte SW_TX_out = 5;   // Arduino Pin for transmit 
const int BAUD = 9600;   // Tx & Rx rate

//const byte PIN_LED1 = 10;
//const byte PIN_LED2 = 11;

int listen_flag = true;
int tx_data = 22; // to transmit
int rx_data = 0; 
  
// Set up a software serial instance
//SoftwareSerial SW(SW_RX_in, SW_TX_out);

void setup() {
  // put your setup code here, to run once:
  
  // set up IO pins
  //pinMode(PIN_LED1, OUTPUT);
  //pinMode(PIN_LED2, OUTPUT);
  
  // set up SW Serial 
  //pinMode(SW_RX_in, INPUT);
  //pinMode(SW_TX_out, OUTPUT);
  Serial3.begin(BAUD);
    
  // Set up Serial to Computer COM port
  Serial.begin(9600);
  // Serial print (status & troubleshooting)
  Serial.println("\nEnd of void setup()");
  Serial.print("test print value = "); Serial.print("3");

}

void loop() {
  // put your main code here, to run repeatedly:

  SW.listen();
  
  if ( SW.isListening()  ) {
    //Serial.println("\nSW serial listening"); 
    listen_flag = false;
  
    //SW.write(tx_data); // send it
    //Serial.print("tx data sent, value: ");Serial.print(tx_data);

    // if there is anything in the buffer
    if ( SW.available() > 0 ) { 
      rx_data = SW.read()-'0'; // apparently an ASCII value, convert to number
      Serial.print("\ndata received, value: ");
      Serial.print(rx_data);
    }

    // what to do with the info
    if (rx_data == 1) {
      // any arbitrary code here
      Serial.print("\ndata received, first button pressed");
      digitalWrite(PIN_LED1, HIGH);
      digitalWrite(PIN_LED2, LOW);
    }
    if (rx_data == 2) {
      // any arbitrary code here
      Serial.print("\ndata received, second button pressed");
      digitalWrite(PIN_LED1, LOW);
      digitalWrite(PIN_LED2, HIGH);
    }          
    if (rx_data == 3) {
      // any arbitrary code here
      Serial.print("\ndata received, third button pressed");
      digitalWrite(PIN_LED1, HIGH);
      digitalWrite(PIN_LED2, HIGH);
    }
    // resets variable - could be implemented without this
    // except the serial monitor fills up quickly 
    rx_data = 0;
  }
}
