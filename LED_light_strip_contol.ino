#include "FastLED.h"

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

#define CLOCK_PIN 13

// Define the array of leds
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];
CRGB leds7[NUM_LEDS7];

void setup() {
     
     pinMode(5,  INPUT);   // hard switch that might be removed later
     
     pinMode(8,  INPUT);   // GPIO pins from Computer science team
     pinMode(9,  INPUT);
     pinMode(10, INPUT);
     pinMode(11, INPUT);
     
     FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds3, NUM_LEDS3);
     FastLED.addLeds<NEOPIXEL, DATA_PIN4>(leds4, NUM_LEDS4);
     FastLED.addLeds<NEOPIXEL, DATA_PIN5>(leds5, NUM_LEDS5);
     FastLED.addLeds<NEOPIXEL, DATA_PIN6>(leds6, NUM_LEDS6);
     FastLED.addLeds<NEOPIXEL, DATA_PIN7>(leds7, NUM_LEDS7);
}

int switch1=0;
int x = 0;

void loop() {
  
     // Read GPIO pins (will need to change to seireal input later probably)
     int Bit0 = digitalRead(8);
     int Bit1 = digitalRead(9);
     int Bit2 = digitalRead(10);
     int Bit3 = digitalRead(11);
     int DisplayMode = 0;           // Set to 0 for testing code
     
     // Light all stands in white for testing
     if(DisplayMode == 0){
          leds3[x++] = CRGB::White;
          FastLED.show();
          leds4[x++] = CRGB::Green;
          FastLED.show();
          leds5[x++] = CRGB::Blue;
          FastLED.show();
          leds6[x++] = CRGB::Red;
          FastLED.show();
          leds7[x++] = CRGB::Black;
          FastLED.show();
     }
     
     // Light all strands off for testing
     else if(DisplayMode == 1){
     
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
     
     // set x to the value of the number of light segment you want to illuminate
     // segments are 0 - 39 (confirmed 1/26/22)
     //switch1 = digitalRead(5);
     //for (x=0;x<40;x++)
     // need to find a way to input RGB code instead of 'color'
     //leds[x] = CRGB::Pink;
     //leds[35] = CRGB::Pink;
     //FastLED.show();

}


// TESTED & WORKING 1/26 
//  int x = 0;
//  for (x=0;x<40;x++)
//    // need to find a way to input RGB code instead of 'color'
//    leds[x] = CRGB::Pink;
//    //leds[35] = CRGB::Pink;
//  FastLED.show();
// }


// Random code that has no use to anyone!
//void loop() { 
 // int i =0;
 // while (i < 49) {
 //   leds[i] = CRGB::Pink;
 //   FastLED.show();
 //   delay(20);
 //   leds[i] = CRGB::Green;
 //   i++;
 // }
 // i =50;
 // while (i > 0) {
 //   leds[i] = CRGB::Green;
 //   FastLED.show();
 //   delay(20);
 //   leds[i] = CRGB::Black;
 //   i = i -1;
 // }
 // Turn the LED on, then pause

 //FastLED.show();
 //delay(500);
 // Now turn the LED off, then pause
 //leds[0] = CRGB::Black;
 //FastLED.show();
 //delay(500);
//}
