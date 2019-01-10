#include <WiFi.h>
#include "lib.h"

// custom config
const char* networkSSID = "ITA";
const char* networkPassword = "Pruefung2018";

// THE following is magic :D ... dON'T tOUCH iT!

void setup() {
  Serial.begin( 115200 );
  Serial.println( "Connecting to Wifi ..." );
  connectToWifi( networkSSID, networkPassword );
  Serial.println( "Connecting to Picroft ..." );
  connectToServer();
  Serial.println( "Init Communication ..." );
  initCommunication();
  Serial.println( "Running!" );
}

void loop() {
  handleCommunication();
}
