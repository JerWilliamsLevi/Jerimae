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
  
     pinMode(2,  INPUT);   // hard switch that might be removed later
     
     // Data from CS currently planned to go over LAN connection (http web server)     
  
     FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds3, NUM_LEDS3);
     FastLED.addLeds<NEOPIXEL, DATA_PIN4>(leds4, NUM_LEDS4);
     FastLED.addLeds<NEOPIXEL, DATA_PIN5>(leds5, NUM_LEDS5);
     FastLED.addLeds<NEOPIXEL, DATA_PIN6>(leds6, NUM_LEDS6);
     FastLED.addLeds<NEOPIXEL, DATA_PIN7>(leds7, NUM_LEDS7);
     
     // pin 8 will be the signal input from the PIR snesor. When there is no
     // movement the signal will go LOW and when movement is detected the signal
     // will go HIGH
}


void loop() {

  // central core, light string 1
  for( int x3=0; x3<40; x3++){
    leds3[x3] = 0;
  }

  // light string 2
  for( int x4=0; x4<4; x4++){ // sun sensors
    leds4[x4] = 0x00ffff;
  }
  for( int x4=4; x4<7; x4++){
    leds4[x4] = 0;
  }
  for( int x4=6; x4<8; x4++){ // cold gas thruster A
    leds4[x4] = 0x00ffff;
  }
  for( int x4=8; x4<15; x4++){
    leds4[x4] = 0;
  }
  for( int x4=15; x4<20; x4++){ // SP Thruster
    leds4[x4] = 0x00ffff;
  }
  for( int x4=20; x4<21; x4++){
    leds4[x4] = 0;
  }
  for( int x4=21; x4<25; x4++){ // SP Thruster
    leds4[x4] = 0x00ffff;
  }
  for( int x4=25; x4<31; x4++){
    leds4[x4] = 0;
  }
  for( int x4=31; x4<34; x4++){ // cold gas thruster A
    leds4[x4] = 0x00ffff;
  }
  for( int x4=34; x4<35; x4++){
    leds4[x4] = 0;
  }
  for( int x4=35; x4<40; x4++){ // Sun Sensors
    leds4[x4] = 0x00ffff;
  }

  // turn light strip 2 all off
  for( int x4=0; x4<40; x4++){
    leds4[x4] = CRGB::Black;
  }

  // light strip 3
  for( int x5=0; x5<4; x5++){ // Sun Sensors
    leds5[x5] = 0x00ffff;
  }
  for( int x5=4; x5<7; x5++){
    leds5[x5] = 0;
  }
  for( int x5=7; x5<40; x5++){ // DSOC
    leds5[x5] = 0xffcc00;
  }

  // turn light strip 3 all off
  for( int x5=0; x5<40; x5++){
    leds5[x5] = 0;
  }

  // light strip 4
  for( int x6=0; x6<3; x6++){ // cold gas thruster A
    leds6[x6] = 0x00ffff;
  }
  for( int x6=3; x6<10; x6++){
    leds6[x6] = CRGB::Black;
  }
  for( int x6=10; x6<16; x6++){ // star trackers
    leds6[x6] = 0x00ffff;
  }
  for( int x6=16; x6<18; x6++){
    leds6[x6] = CRGB::Black;
  }
  for( int x6=18; x6<23; x6++){ // star trackers
    leds6[x6] = 0x00ffff;
  }
  for( int x6=23; x6<27; x6++){
    leds6[x6] = CRGB::Black;
  }
  for( int x6=27; x6<30; x6++){ // cold gas thruster A
    leds6[x6] = 0x00ffff;
  }
  for( int x6=30; x6<34; x6++){
    leds6[x6] = CRGB::Black;
  }
  for( int x6=34; x6<40; x6++){ // Sun Sensor
    leds6[x6] = 0x00ffff;
  }

  // turn light strip 3 all off
  for( int x6=0; x6<40; x6++){
    leds6[x6] = 0;
  }
  
  for( int x7=0; x7<40; x7++){
    leds7[x7] = CRGB::Black;
  }

  
  FastLED.show();
  
}
    
