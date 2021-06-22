#include <Arduino.h>
#include <SD.h>

// change this to match your SD shield or module;
//     Arduino Ethernet shield: pin 4
//     Adafruit SD shields and modules: pin 10
//     Sparkfun SD shield: pin 8
const int chipSelect = 4;
const char configFileName[] = "config.ini";

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File configFile = SD.open(configFileName);

  // if the file is available, write to it:
  if (configFile) {
    while (configFile.available()) {
      Serial.write(configFile.read());
    }
    configFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.print("error opening configuration file ");
    Serial.println(configFileName);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
