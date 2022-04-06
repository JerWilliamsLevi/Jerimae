# Arduino Code for NASA Psyche Project

Use this area to show how to connect the board to everything

ELEGOO PIN LAYOUT        Digital

Digital PIN 0 = Logic 0

Digital PIN 1 = Logic 1

Digital PIN 2 = Hard Switch that might be removed later

Digital PIN 3 = Led Light Strip 1

Digital PIN 4 = Led Light Strip 2

Digital PIN 5 = Led Light Strip 3

Digital PIN 6 = Led Light Strip 4

Digital PIN 7 = Led Light Strip 5

Digital PIN 12= IR Remote data pin



       //      IR remote decode
       // POWER    = 13598  | sleep/wake
       // UP       = 27399  | next group
       // DOWN     = -6218  | previous group
       // Left     = 28282  | previous object
       // Right    = 4795   | next object
       // TOPL     = -15554 | Navigation
       // TOPR     = -22246 | Science
       // BotR     = -19202 | Comunication
       // BotL     = 5150   | Structure
       // BottomL  = 20023  | Cold Gas Thruster
       // BottomR  = 30879  | SPThruster
       // remote 0 = -8326  | 
       // remote 1 = 22907  | Magnetometer
       // remote 2 = 31102  | Gamma Ray Spectrometer
       // remote 3 = 7615   | Neutron Specctrometer
       // remote 4 = 21462  | Multi Spectral Imagers
       // remote 5 = 20191  | Low Gain Antenna
       // remote 6 = -9574  | X-Band High Gain Antenna
       // remote 7 = 32475  | DSOC Assembly
       // remote 8 = 3710   | Star Trackers
       // remote 9 = 7031   | Sun Sensors
