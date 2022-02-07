#include "FastLED.h"
// How many leds in your strip?
#define NUM_LEDS 50
// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
void setup() {
     pinMode(5, INPUT); 
     // Uncomment/edit one of the following lines for your leds arrangement.
     // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
     FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
     // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
     // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}
int switch1=0;
int x = 0;
void loop() {
  // set x to the value of the number of light segment you want to illuminate
  // segments are 0 - 39 (confirmed 1/26/22)
switch1 = digitalRead(5);
for (x=0;x<40;x++)
   // need to find a way to input RGB code instead of 'color'
   leds[x] = CRGB::Pink;
   //leds[35] = CRGB::Pink;
   FastLED.show();

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
