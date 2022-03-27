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

#include "FastLED.h"
#include <IRremote.h>
#include <SPI.h>
#include <Ethernet.h>

// ---------- LAN setup info
byte mac[] = { 0xA9, 0xB9, 0xC9, 0xD9, 0xE9, 0xF9 }; // MAC address
IPAddress ip(192, 168, 0, 32);  // IP (depends on local network)
EthernetServer server(8224); // initialize with port 8224

// Set up for IR Remote
const int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Number of LEDs in light strip
// set to 50 for test strip
#define NUM_LEDS3 50
#define NUM_LEDS4 50
#define NUM_LEDS5 50
#define NUM_LEDS6 50
#define NUM_LEDS7 50

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
     irrecv.enableIRIn();  // IR remote
     
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
int PIRsensor = 0;

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
    if ( request.startsWith("POST /1") ) {
      DisplayMode = 1;
    }
    if ( request.startsWith("POST /2") ) {
      DisplayMode = 2;
    }
    if ( request.startsWith("POST /3") ) {
      DisplayMode = 3;
    }

    // close the connection:
    client.stop();
    Serial.println("\nclient disconnected");
     }
     // -----------------------------------
  
     // IR remote read
     if (irrecv.decode(&results)){      // Read Remote Values
           remote = (results.value);    // Set remote values to variable "remote"
           irrecv.resume();             // Continue searching for remote values
       
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
       
           int DisplayMode = 0; // Later the display mode will be set by the serial input from the UI PC
       
           // Light all strands in for testing
           if(remote == 26775 || DisplayMode ==0){
                int x = 0;
                while(x<50){
                      leds3[x] = CRGB::Black;
                      leds4[x] = CRGB::Black;
                      leds5[x] = CRGB::Black;
                      leds6[x] = CRGB::Black;
                      leds7[x] = CRGB::Black;
                      FastLED.show();
                      x=x+1;
                }
           }
           
           // Light all strands off for testing
           else if(remote == 12495 || DisplayMode ==1){
                 int x = 0;
                      while(x<50){
                            leds3[x] = CRGB::White;
                            leds4[x] = CRGB::Green;
                            leds5[x] = CRGB::Blue;
                            leds6[x] = CRGB::Red;
                            leds7[x] = CRGB::Black;
                            FastLED.show();
                      x=x+1;
                }
           }
           else if(DisplayMode == 2){
           // Will plan various other modes later
           }
           else if(DisplayMode == 3){
           // Will plan various other modes later
           }
           else if(DisplayMode == 4){
           // Will plan various other modes later
           }
           else if(DisplayMode == 5){
           // Will plan various other modes later
           }
           else if(DisplayMode == 6){
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
     }
}
