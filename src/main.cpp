#include <Arduino.h>
#include <SD.h>
#include <Ethernet.h>

// change this to match your SD shield or module;
//      pin 4:  Arduino Ethernet shield
//      pin 10: Adafruit SD shields and modules
//      pin 8:  Sparkfun SD shield
const int sdPin = 4;

// change this to macht your ethernet shield or module CS pin
//      pin 10: Most Arduino shields
//      pin 5:  MKR ETH shield
//      pin 0:  Teensy 2.0
//      pin 20: Teensy++ 2.0
//      pin 15: ESP8266 with Adafruit Featherwing Ethernet
//      pin 33: ESP32 with Adafruit Featherwing Ethernetconst int etherPin = 10;
const int ethernetPin = 10;

const char configFileName[] = "config.ini";
char hostname[] = "reinis-arduino-smart-switch";
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(10, 14, 1, 200);
int port = 80;
EthernetServer server(port);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(sdPin, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(sdPin)) {
    Serial.println("Card failed, or not present");
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File configFile = SD.open(configFileName);

  // if the file is available, print content
  if (configFile) {
    while (configFile.available()) {
      Serial.write(configFile.read());
    }
    configFile.close();
    Serial.println();
    Serial.println();
  }
  // if the file isn't open, pop up an error
  else {
    Serial.print("error opening configuration file ");
    Serial.println(configFileName);
  }

  Serial.print("Initializing ethernet shield...");
  Ethernet.init(ethernetPin);
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("ethernet shield was not found.  Sorry, can't run without hardware.");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("ethernet cable is not connected.");
  }
  Serial.print("ip address is ");
  Serial.println(Ethernet.localIP());

  Serial.print("Start webserver ");
  Serial.print(hostname);
  Serial.print(" on port ");
  Serial.print(port);
  Serial.println(" and waiting for connections ...");
  server.begin();
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Webserver - new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 10");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>");
          client.println(hostname);
          client.println("</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>");
          client.println(hostname);
          client.println("</h1>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</body>");
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
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("Webserver - client disconnected");
  }
}
