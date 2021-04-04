#include "TinyGPS++.h"
#include <SoftwareSerial.h>
TinyGPSPlus gps;
int tx = 10;
int rx = 9;
SoftwareSerial mySerial(rx, tx);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  mySerial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
    while(mySerial.available() > 0)
        gps.encode(mySerial.read());
    if (gps.location.isUpdated())
    {
        Serial.print("LAT = "); Serial.println(gps.location.lat(), 6);
        Serial.print("LNG = "); Serial.println(gps.location.lng(),6); Serial.println(" ");
    }
    // Serial.print("LAT = "); Serial.println(gps.location.lat(), 6);
}
