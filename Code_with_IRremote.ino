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
// Digital PIN 12= IR Remote data pin
//
//        Analog
//        Serial

#include "FastLED.h"
#include <IRremote.h>


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
     
     pinMode(8,  INPUT);   // GPIO pins from Computer science team
     pinMode(9,  INPUT);
     pinMode(10, INPUT);
     pinMode(11, INPUT);
     
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
