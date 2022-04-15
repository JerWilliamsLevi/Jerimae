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
// FQDN: WIZnetD9E9F9.istb4.dhcp.asu.edu
// DNS () :
//    129.219.13.81, 129.219.17.5, 129.219.17.200

byte mac[] = { 0x00, 0x25, 0xCA, 0xD9, 0xE9, 0xF9 }; // MAC address
EthernetServer server(80); // initialize with port 8224

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
#define NUM_LEDS3 50
#define NUM_LEDS4 50
#define NUM_LEDS5 50
#define NUM_LEDS6 50
#define NUM_LEDS7 50
#define NUM_LEDS8 50

#define DATA_PIN3 3 // lighting pin for central cylinder
#define DATA_PIN4 4 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN5 5 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN6 6 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN7 7 // Lighting points for other introments (pin and names adjusted later)
#define DATA_PIN8 8 // Lighting points for other introments (pin and names adjusted later)

//// Define the array of leds
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];
CRGB leds7[NUM_LEDS7];
CRGB leds8[NUM_LEDS8];

void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();  // IR remote
     
  pinMode(2, INPUT);   // hard switch that might be removed later
     
  pinMode(11, OUTPUT); // reset pin for ethernet
  
  // Data from CS currently planned to go over LAN connection (http web server)     
  Ethernet.init(10);
  digitalWrite(11, LOW);
  delay(500); 
  digitalWrite(11, HIGH);
  Ethernet.begin(mac);
  server.begin();
  
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  Serial.print("gateway ip is ");
  Serial.println(Ethernet.gatewayIP());
    
  FastLED.addLeds<NEOPIXEL, DATA_PIN3>(leds3, NUM_LEDS3);
  FastLED.addLeds<NEOPIXEL, DATA_PIN4>(leds4, NUM_LEDS4);
  FastLED.addLeds<NEOPIXEL, DATA_PIN5>(leds5, NUM_LEDS5);
  FastLED.addLeds<NEOPIXEL, DATA_PIN6>(leds6, NUM_LEDS6);
  FastLED.addLeds<NEOPIXEL, DATA_PIN7>(leds7, NUM_LEDS7);
  FastLED.addLeds<NEOPIXEL, DATA_PIN8>(leds8, NUM_LEDS8);
     
  for( int x3=0; x3<40; x3++){leds3[x3] = CRGB::Black;}
  for( int x4=0; x4<40; x4++){leds4[x4] = CRGB::Black;}
  for( int x5=0; x5<40; x5++){leds5[x5] = CRGB::Black;}
  for( int x6=0; x6<40; x6++){leds6[x6] = CRGB::Black;}
  for( int x7=0; x7<40; x7++){leds7[x7] = CRGB::Black;}
  for( int x8=0; x8<46; x8++){leds8[x8] = CRGB::Black;}

}

int remote = 0;
int remotefunction(); String remoteInterpret(String request, double remote);
int PIRsensor = 0;
int DisplayMode = 0;

void loop() {
       
  // ---------- http webserver ------------------
  // listen for incoming clients
  Ethernet.maintain();
  EthernetClient client = server.available();
  if (client){// || receiver.decode(&results)) {
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
    remote = 0;
    remote  = remotefunction(); // get remote codes
    Serial.println(remote);
    request = remoteInterpret(request, remote); // more remote nonsence
    Serial.print(request); // print the request (debugging)
    // check what has been pressed
    if ( request.startsWith("POST /1 ") ) {
      all_off();
      for( int x7=8;  x7<13; x7++){leds7[x7] = 0x40ff00;} // Multi Spectral Imager
      for( int x7=14; x7<19; x7++){leds7[x7] = 0x40ff00;} // Multi Spectral Imager
      for( int x8=39; x8<45; x8++){leds8[x8] = 0x40ff00;} // Magnetometer
      for( int x8=0;  x8<6;  x8++){leds8[x8] = 0x40ff00;} // Gamma Ray Spectrometer
      for( int x8=6;  x8<12; x8++){leds8[x8] = 0x40ff00;} // Neutron Spectrometer
    }
    else if ( request.startsWith("POST /2") ) {
      all_off();
      for( int x8=39; x8<45; x8++){leds8[x8] = 0x40ff00;} // Magnetometer
    }
    else if ( request.startsWith("POST /3") ) { 
      all_off();
      for( int x8=0;  x8<6; x8++){leds8[x8] = 0x40ff00;} // Gamma Ray Spectrometer
    }
    else if ( request.startsWith("POST /4") ) {
      all_off();
      for( int x8=6;  x8<12; x8++){leds8[x8] = 0x40ff00;} // Neutron Spectrometer
    }
    else if ( request.startsWith("POST /5") ) {
      all_off();
      for( int x7=8;  x7<13; x7++){leds7[x7] = 0x40ff00;} // Multi Spectral Imager
      for( int x7=14; x7<19; x7++){leds7[x7] = 0x40ff00;} // Multi Spectral Imager
    }
    else if ( request.startsWith("POST /6") ) {
      all_off();
    }
    else if ( request.startsWith("POST /7") ) { // Communication
      all_off();
      for( int x5=7;  x5<40; x5++){leds5[x5] = 0xffcc00;} // DSOC
      for( int x8=12; x8<39; x8++){leds8[x8] = 0xffbb00;} // X Band Antenna  
    }
    else if ( request.startsWith("POST /8") ) {
      all_off(); 
      for( int x8=12; x8<39; x8++){leds8[x8] = 0xffbb00;} // X Band Antenna
    }
    else if ( request.startsWith("POST /9") ) { // DSOC
      all_off();
      for( int x5=7;  x5<40; x5++){leds5[x5] = 0xffcc00;} // DSOC
    }
    else if ( request.startsWith("POST /10") || remote == 1) { // Navigation
      all_off();    
      for( int x4=15; x4<20; x4++){leds4[x4] = 0x00ffff;} // SP Thruster
      for( int x4=21; x4<25; x4++){leds4[x4] = 0x00ffff;} // SP Thruster
      for( int x4=6;  x4<8;  x4++){leds4[x4] = 0x00ffff;} // cold gas thruster A
      for( int x4=31; x4<34; x4++){leds4[x4] = 0x00ffff;} // cold gas thruster A
      for( int x6=0;  x6<3;  x6++){leds6[x6] = 0x00ffff;} // cold gas thruster A
      for( int x6=27; x6<30; x6++){leds6[x6] = 0x00ffff;} // cold gas thruster A
      for( int x7=0;  x7<3;  x7++){leds7[x7] = 0x00ffff;} // cold gas thruster A
      for( int x7=25; x7<28; x7++){leds7[x7] = 0x00ffff;} // cold gas thruster A
      for( int x6=10; x6<16; x6++){leds6[x6] = 0x00ffff;} // star trackers
      for( int x6=18; x6<23; x6++){leds6[x6] = 0x00ffff;} // star trackers
      for( int x4=0;  x4<4;  x4++){leds4[x4] = 0x00ffff;} // Sun Sensors
      for( int x4=35; x4<40; x4++){leds4[x4] = 0x00ffff;} // Sun Sensors
      for( int x5=0;  x5<4;  x5++){leds5[x5] = 0x00ffff;} // Sun Sensors
      for( int x6=34; x6<40; x6++){leds6[x6] = 0x00ffff;} // Sun Sensors
    }
    else if ( request.startsWith("POST /11") ) { // Cold Gas Thrusters
      all_off();
      for( int x4=6;  x4<8;  x4++){leds4[x4] = 0x00ffff;} // cold gas thruster A
      for( int x4=31; x4<34; x4++){leds4[x4] = 0x00ffff;} // cold gas thruster A
      for( int x6=0;  x6<3;  x6++){leds6[x6] = 0x00ffff;} // cold gas thruster A
      for( int x6=27; x6<30; x6++){leds6[x6] = 0x00ffff;} // cold gas thruster A
      for( int x7=0;  x7<3;  x7++){leds7[x7] = 0x00ffff;} // cold gas thruster A
      for( int x7=25; x7<28; x7++){leds7[x7] = 0x00ffff;} // cold gas thruster A
    }
    else if ( request.startsWith("POST /12") ) { // Star Trackers
      all_off();
      for( int x6=10; x6<16; x6++){leds6[x6] = 0x00ffff;} // star trackers
      for( int x6=18; x6<23; x6++){leds6[x6] = 0x00ffff;} // star trackers
    }
    else if ( request.startsWith("POST /13") ) {
      all_off();
      for( int x4=0;  x4<4;  x4++){leds4[x4] = 0x00ffff;} // Sun Sensors
      for( int x4=35; x4<40; x4++){leds4[x4] = 0x00ffff;} // Sun Sensors
      for( int x5=0;  x5<4;  x5++){leds5[x5] = 0x00ffff;} // Sun Sensors
      for( int x6=34; x6<40; x6++){leds6[x6] = 0x00ffff;} // Sun Sensors
    } 
    else if ( request.startsWith("POST /14") ) { // SP Thrusters
      all_off();
      for( int x4=15; x4<20; x4++){leds4[x4] = 0x00ffff;} // SP Thruster
      for( int x4=21; x4<25; x4++){leds4[x4] = 0x00ffff;} // SP Thruster
    }
    else if ( request.startsWith("POST /15") ) { // central core, light string 1
      all_off();
      for( int x3=0; x3<40; x3++){leds3[x3] =CRGB::Pink;} // Central Core
    }
    else if ( request.startsWith("POST /0") ) {// 0 means off
       all_off();
    }
    
    // place holder for receiving day/time/sleepmode data
    //    else if ( request.startsWith("POST /TIME") ) {
    //      ;
    //    }
  
    // close the connection:
    client.stop();
    Serial.println("\nclient disconnected");
  }
  // -----------------------------------   

  FastLED.show();
}

int all_off(){
  for( int x3=0; x3<40; x3++){
    leds3[x3] = CRGB::Black;
  }
  for( int x4=0; x4<40; x4++){
    leds4[x4] = CRGB::Black;
  }
  for( int x5=0; x5<40; x5++){
    leds5[x5] = CRGB::Black;
  }
  for( int x6=0; x6<40; x6++){
    leds6[x6] = CRGB::Black;
  }
  for( int x7=0; x7<40; x7++){
    leds7[x7] = CRGB::Black;
  }
  for( int x8=0; x8<46; x8++){
    leds8[x8] = CRGB::Black;
  }
}

int remotefunction()              // function to load IR code
{
  while
    (
    remote!= 13598||remote!= 27399||remote!=111111||
    remote!=-6218 ||remote!=28282 ||remote!=4795  ||
    remote!=-15554||remote!=-22246||remote!=-19202|| 
    remote!=5150  ||remote!=20023 ||remote!=30879 ||
    remote!=-8326 ||remote!=22907 ||remote!=31102 ||
    remote!=7615  ||remote!=21462 ||remote!=20191 ||
    remote!=-9574 ||remote!=32475 ||remote!=3710  ||
    remote!=7031 
    )
  {
    if (receiver.decode(&results))
    {
      receiver.resume();
      remote = results.value;
      Serial.print("The remote code in the loop = ");
      Serial.println(results.value);
      if(
        remote== 13598||remote== 27399||remote==111111||
        remote==-6218 ||remote==28282 ||remote==4795  ||
        remote==-15554||remote==-22246||remote==-19202|| 
        remote==5150  ||remote==20023 ||remote==30879 ||
        remote==-8326 ||remote==22907 ||remote==31102 ||
        remote==7615  ||remote==21462 ||remote==20191 ||
        remote==-9574 ||remote==32475 ||remote==3710  ||
        remote==7031  || remote == 0
        )
      {
        
        Serial.print("The remote code being sent from the function = ");
        Serial.println(remote);
        return remote;
      }
    }
  }
}

String remoteInterpret(String request, double remote){
   if (remote == 13598){
     if (request.startsWith("POST /6")){request = "POST /1";}  // sleep/wake
     else {request = "POST /6";}
   }
   else if (remote == 27399)                                        // Cycle through group 10->1->7->15
   {
     if (request.startsWith("POST /10")){request = "POST /1";}          
     else if (request.startsWith("POST /1")){request = "POST /7";}          
     else if (request.startsWith("POST /7")){request = "POST /15";}          
     else if (request.startsWith("POST /15")){request = "POST /10";}          
     else {request = "POST /10";}          
   }
   else if (remote == -6128)                                        // Cycle through group backward
   {
     if (request.startsWith("POST /15")){request = "POST /7";}          
     else if (request.startsWith("POST /7")){request = "POST /1";}          
     else if (request.startsWith("POST /1")){request = "POST /10";}          
     else if (request.startsWith("POST /10")){request = "POST /15";}          
     else {request = "POST /10";}          
   }
   else if (remote == 28282)                                        // Cycle through object
   {                                                                // order 11 14 2 3 4 5 6 8 9 10 12
     if (request.startsWith("POST /11")){request = "POST /14";}
     else if (request.startsWith("POST /14")){request = "POST /2";}
     else if (request.startsWith("POST /2")){request = "POST /3";}
     else if (request.startsWith("POST /3")){request = "POST /4";}
     else if (request.startsWith("POST /4")){request = "POST /5";}
     else if (request.startsWith("POST /5")){request = "POST /6";}
     else if (request.startsWith("POST /6")){request = "POST /8";}
     else if (request.startsWith("POST /8")){request = "POST /9";}
     else if (request.startsWith("POST /9")){request = "POST /10";}
     else if (request.startsWith("POST /10")){request = "POST /12";}
     else {request = "POST /11";}
   }
   else if (remote == 4795)                                         // Cycle through object in reverse
   {
     if (request.startsWith("POST /12")){request = "POST /10";}
     else if (request.startsWith("POST /10")){request = "POST /9";}
     else if (request.startsWith("POST /9")){request = "POST /8";}
     else if (request.startsWith("POST /8")){request = "POST /6";}
     else if (request.startsWith("POST /6")){request = "POST /5";}
     else if (request.startsWith("POST /5")){request = "POST /4";}
     else if (request.startsWith("POST /4")){request = "POST /3";}
     else if (request.startsWith("POST /3")){request = "POST /2";}
     else if (request.startsWith("POST /2")){request = "POST /14";}
     else if (request.startsWith("POST /14")){request = "POST /11";}
     else {request = "POST /11";}
   }
   else if (remote == -15554){request = "POST /10";} // Navigation
   else if (remote == -22246){request = "POST /1";} // Science
   else if (remote == -19202){request = "POST /7";} // Comunication
   else if (remote == 5150)  {request = "POST /15";} // Structure
   else if (remote == 20023) {request = "POST /11";} // cold gas thrusters
   else if (remote == 30879) {request = "POST /14";} // SP Thrusters
   else if (remote == -8326) {request = "POST /";}   // not used
   else if (remote == 22907) {request = "POST /2";} // Magnetometer
   else if (remote == 31102) {request = "POST /3";} // Gamma Ray Spectrometer
   else if (remote == 7615)  {request = "POST /4";} // Neutron Spectrometer
   else if (remote == 21462) {request = "POST /5";} // Multi Spectral Imager
   else if (remote == 20191) {request = "POST /6";} // All Off I guess
   else if (remote == -9574) {request = "POST /8";} // X Band Antenna
   else if (remote == 32475) {request = "POST /9";} // DSOC
   else if (remote == 3710)  {request = "POST /12";} // Start trackers
   else if (remote == 7031)  {request = "POST /13";} // Sun Sensors
   else                      {request = request;}
   // DOWN     = -6218  | previous group
   // Left     = 28282  | previous object
   // Right    = 4795   | next object
   // TOPL     = -15554 | Navigation 
   // TOPR     = -22246 | Science
   // BotR     = -19202 | Comunication
   // BotL     = 5150   | Structure
   // BottomL  = 20023  | Cold Gas Thruster
   // BottomR  = 30879  | SPThruster
   // remote 0 = -8326  | central cylinder
   // remote 1 = 22907  | Magnetometer
   // remote 2 = 31102  | Gamma Ray Spectrometer Post 3
   // remote 3 = 7615   | Neutron Specctrometer         
   // remote 4 = 21462  | Multi Spectral Imagers
   // remote 5 = 20191  | Low Gain Antenna
   // remote 6 = -9574  | X-Band High Gain Antenna
   // remote 7 = 32475  | DSOC Assembly
   // remote 8 = 3710   | Star Trackers
   // remote 9 = 7031   | Sun Sensors
   return request;
}
