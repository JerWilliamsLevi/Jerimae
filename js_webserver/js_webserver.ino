/*
  Web Server
  to accept http get requests from javascript

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 modified 26 Mar 2022
 by Cecilia Delcamp
 for use in Psyche Remote Exhibit
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xA9, 0xB9, 0xC9, 0xD9, 0xE9, 0xF9 };
IPAddress ip(192, 168, 0, 32);
EthernetServer server(8224); // initialize with port 8224

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;

    String request = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request = request + c;

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("</html>");
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


    // check what has been pressed
    if ( request.startsWith("GET /1 HTTP/1.1") ) {
      Serial.print("First Button");
    }
    if ( request.startsWith("GET /2 HTTP/1.1") ) {
      Serial.print("Second Button");
    }
    if ( request.startsWith("GET /3 HTTP/1.1") ) {
      Serial.print("Third Button");
    }
    
    // give the web browser time to receive the data
    delay(1);
    
    // close the connection:
    client.stop();
    Serial.println("\nclient disconnected");
  }
}
