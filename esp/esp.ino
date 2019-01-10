#include <WiFi.h>

// custom config
const char* networkSSID = "test";
const char* networkPassword = "pass";

// THE following is magic :D ... dON'T tOUCH iT!
const int port = 6522;
WiFiClient client;

void connectToWifi();
void connectToServer();
void initCommunication();
void handleCommunication();
char* getBroadcastAddress(char* ip);

void setup() {
  Serial.begin( 115200 );
  Serial.println( "Connecting to Wifi ..." );
  connectToWifi();
  Serial.println( "Connecting to Picroft ..." );
  connectToServer();
  Serial.println( "Init Communication ..." );
  initCommunication();
  Serial.println( "Running!" );
}

void loop() {
  handleCommunication();
}

void connectToWifi() {
  WiFi.begin( networkSSID, networkPassword );
  while ( WiFi.status() != WL_CONNECTED ) {}
  char* broadcastIp = getBroadcastIp( WiFi.localIp() );
  Serial.print( "Broadcast IP: " );
  Serial.println( broadcastIp );
}

void connectToServer() {
  char* broadcastIp = getBroadcastIp( WiFi.localIp() );
  Serial.print( "Broadcast IP: " );
  Serial.println( broadcastIp );

  if ( !client.connect( broadcastIp, port ) ) {
    Serial.print( "Failed to Connect. " );
    delay( 1000 );
    Serial.print( "Next try ..." );
  }
}

void initCommunication() {
  
}

void handleCommunication() {
  
}

char* getBroadcastAddress(char* ip) {
   int i, j;
   char c;
   char newIp[16];
   for (i = 0, j = 0; i < 15 && (c = ip[i]) != NULL && j < 3; i++) {
    if (c == '.') {
      j++;
    }
   }
   strncpy(newIp, ip, i - 1);
   strncpy(&newIp[i], "255", 3);
   return newIp;
}
  
