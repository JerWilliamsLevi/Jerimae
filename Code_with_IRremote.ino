//   ELEGOO PIN LAYOUT
//        Digital
// Digital PIN 0 = Logic 0
// Digital PIN 1 = Logic 1
// Digital PIN 2 = Hard Switch that might be removed later
// Digital PIN 3 = Led Light Strip 1
// Digital PIN 4 = Led Light Strip 2
// Digital PIN 5 = Led Light Strip 3
// Digital PIN 6 = Led Light Strip 4
// Digital PIN 7 = Led Light Strip 5
// Digital PIN 8 = PIR sensor
// Digital PIN 10 = Ethernet Board NSS pin
// Digital PIN 11 = Ethernet Board RST pin
// Digital PIN 12= IR Remote data pin
// Digital PIN 50 = Ethernet Board MI pin
// Digital PIN 51 = Ethernet Board MO pin
// Digital PIN 52 = Ethernet Board SCK pin
//
//        Analog
//        Serial


// this is a line to see if 2 people can edit

// This is also a test

#include "FastLED.h"
#include <IRremote.hpp>
#include <SPI.h>
#include <Ethernet.h>

// ---------- LAN setup info
byte mac[] = { 0xA9, 0xB9, 0xC9, 0xD9, 0xE9, 0xF9 }; // MAC address
IPAddress ip(192, 168, 0, 32);  // IP (depends on local network)
EthernetServer server(8224); // initialize with port 8224

// Set up for IR Remote
const int RECV_PIN = 12;
IRrecv receiver(RECV_PIN);
decode_results results;

// colors for instruments
const int NAVIGATION = 0x00ffff; // BLUE
const int SCIENCE = 0x40ff00; // GREEN
const int COMMUNICATION = 0xffcc00; // YELLOW

// Number of LEDs in light strip
// set to 50 for test strip
#define NUM_LEDS3 40 // 32 ft strands have 40 ICs
#define NUM_LEDS4 40
#define NUM_LEDS5 40
#define NUM_LEDS6 40
#define NUM_LEDS7 40
#define NUM_LEDS8 50 // 15 ft strands have 50 ICs

#define DATA_PIN3 3 // lighting pin for central cylinder
#define DATA_PIN4 4 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN5 5 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN6 6 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN7 7 // Lighting points for other introments (pin and names adjusted later)

//// Define the array of leds
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];
CRGB leds7[NUM_LEDS7];

void setup() {
  
     Serial.begin(9600);
     receiver.enableIRIn();  // IR remote
     
     pinMode(2,  INPUT);   // hard switch that might be removed later
     
     // Data from CS currently planned to go over LAN connection (http web server)     
     Ethernet.begin(mac, ip); // start ethernet connection
     if (Ethernet.linkStatus() == LinkOFF) {
       Serial.println("Ethernet cable is not connected.");
     }
     server.begin();

     Serial.print("server is at ");
     Serial.println(Ethernet.localIP());
  
     FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds3, NUM_LEDS3);
     FastLED.addLeds<NEOPIXEL, DATA_PIN4>(leds4, NUM_LEDS4);
     FastLED.addLeds<NEOPIXEL, DATA_PIN5>(leds5, NUM_LEDS5);
     FastLED.addLeds<NEOPIXEL, DATA_PIN6>(leds6, NUM_LEDS6);
     FastLED.addLeds<NEOPIXEL, DATA_PIN7>(leds7, NUM_LEDS7);
     
     // pin 8 will be the signal input from the PIR snesor. When there is no
     // movement the signal will go LOW and when movement is detected the signal
     // will go HIGH
     pinMode(8, INPUT);   // Pin for PIR sensor
}

int remote = 0;
int remotefunction();
int PIRsensor = 0;
int DisplayMode = 0;

void loop() {
       
  // ---------- http webserver ------------------
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String request = ""; // holds request string

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request = request + c; 

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n");
          client.println("<!DOCTYPE html><html><body>FirstButton</body></html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }

    //Serial.print(request); // print the request (debugging)

    // check what has been pressed
//    if ( request.startsWith("POST /1 ") ) { // Science Group
//      DisplayMode = 1;
//    }
//    else if ( request.startsWith("POST /2") ) { // Magnetometer
//      DisplayMode = 2;
//    }
//    else if ( request.startsWith("POST /3") ) { // Gamma Ray Spectrometer
//      DisplayMode = 3;
//    }
//    else if ( request.startsWith("POST /4") ) { // Neutron Spectrometer
//      DisplayMode = 4;
//    }
//    else if ( request.startsWith("POST /5") ) { // Multi Spectral Imagers
//      DisplayMode = 5;
//    }
//    else if ( request.startsWith("POST /6") ) { // Low Gain Antenna
//      DisplayMode = 6;
//    }
//    else if ( request.startsWith("POST /7") ) { // Communication Group
//      DisplayMode = 7;
//    }
//    else if ( request.startsWith("POST /8") ) { // X Band HG Antenna
//      DisplayMode = 8;
//    }
//    else if ( request.startsWith("POST /9") ) { // DSOC
//      DisplayMode = 9;
//    }
//    else if ( request.startsWith("POST /10") ) { // Navigation Group
//      DisplayMode = 10;
//    }
//    else if ( request.startsWith("POST /11") ) { // Cold Gas Thrusters A & B
//      DisplayMode = 11;
//    }
//    else if ( request.startsWith("POST /12") ) { // Star Trackers
//      DisplayMode = 12;
//    }
//    else if ( request.startsWith("POST /13") ) { // Sun Sensors
//      DisplayMode = 13;
//    }
//    else if ( request.startsWith("POST /14") ) { // SP Thruster
//      DisplayMode = 14;
//    }
//    else if ( request.startsWith("POST /15") ) { // Central Core
//      DisplayMode = 15;
//    }
// place holder for receiving day/time/sleepmode data
//    else if ( request.startsWith("POST /TIME") ) {
//      ;
//    }

    // close the connection:
    client.stop();
    Serial.println("\nclient disconnected");
     }
     // -----------------------------------
  remote = remotefunction();
  delay(1000);
  Serial.println(remote);
       
           //      IR remote decode
           // remote 0 = 26775
           // remote 1 = 12495
           // remote 2 = 6375
           // remote 3 = 31365
           // remote 4 = 4335
           // remote 5 = 14535
           // remote 6 = 23205
           // remote 7 = 17085
           // remote 8 = 19125
           // remote 9 = 21165
       
  // TO USE INCREMENT, DECREMENT, what if we do something like request = "POST /2 "; for 1, "POST /3 "; for 2, etc ?
  
           // Select which lights to turn on
           if(remote == 26775 || request.startsWith("POST /1 ")){ // Science Group
             all_off();
             Magnetometer();
             GammaRay();
             Neutron();
             MultiSpectral();
             LowGainAnt();
           }
           else if(remote == 12495 || "POST /2 "){ // Magnetometer
             all_off();
             Magnetometer();
           }
           else if( "POST /3 "){ // Gamma Ray Spectrometer
             all_off();
             GammaRay();
           }
           else if( "POST /4 "){ // Neutron Spectrometer
             all_off();
             Neutron();
           }
           else if( "POST /5 "){ // Multi Spectral Imagers
             all_off();
             MultiSpectral();
           }
           else if(DisplayMode == 5){ // Low Gain Antenna
             all_off();
             LowGainAnt();
           }
           else if(DisplayMode == 6){ // Communication Group
           // Will plan various other modes later
           }
           else if(DisplayMode == 7){
           // Will plan various other modes later
           }
           else if(DisplayMode == 8){
           // Will plan various other modes later
           }
           else if(DisplayMode == 9){
           // Will plan various other modes later
           }
           else if(DisplayMode == 10){
           // Will plan various other modes later
           }
           else if(DisplayMode == 11){
           // Will plan various other modes later
           }
           else if(DisplayMode == 12){
           // Will plan various other modes later
           }
           else if(DisplayMode == 13){
           // Will plan various other modes later
           }
           else if(DisplayMode == 14){
           // Will plan various other modes later
           }
           else if(DisplayMode == 15){
           // Will plan various other modes later
           }
           else {
             Serial.print("Something went wrong");
           }
          
           FastLED.show();
     }

int all_off()
{
  for( int x3=0; x3<NUM_LEDS3; x3++){
    leds3[x3] = CRGB::Black;
  }
  for( int x4=0; x4<NUM_LEDS4; x4++){
    leds4[x4] = CRGB::Black;
  }
  for( int x5=0; x5<NUM_LEDS5; x5++){
    leds5[x5] = CRGB::Black;
  }
  for( int x6=0; x6<NUM_LEDS6; x6++){
    leds6[x6] = CRGB::Black;
  }
  for( int x7=0; x7<NUM_LEDS7; x7++){
    leds7[x7] = CRGB::Black;
  }
  return(1);
}

int Magnetometer() {
  // not installed 4/6/2022
  // color = SCIENCE
  all_off(); // delete when actual code written;
}
int GammaRay() {
  // not installed 4/6/2022
  // color = SCIENCE
  all_off(); // delete when actual code written;
}
int Neutron() {
    // not installed 4/6/2022
  // color = SCIENCE
  all_off(); // delete when actual code written;
}
int MultiSpectral() {
  for ( int x7 = 8; x7<13; x7++) {
    leds7[x7] = SCIENCE;
  }
  for ( int x7 = 14; x7<19; x7++) {
    leds7[x7] = SCIENCE;
  }
}
int LowGainAnt() {
    // not installed 4/6/2022
  // color = SCIENCE
  all_off(); // delete when actual code written;
}


int remotefunction()              // function to load IR code
{
  if (receiver.decode(&results))
  {
    remote = results.value;
    receiver.resume();
  }
  return (remote);
}
