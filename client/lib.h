
const int port = 6522;
unsigned int lastResponse = 0;
const unsigned int TIMEOUT = 5000; // milliseconds
bool connected = false;
WiFiClient client;

IPAddress getBroadcastAddress(IPAddress subnet, IPAddress ip) {
  return ip | (~subnet);
}

void connectToWifi( const char* ssid, const char* password ) {
  WiFi.begin( (char*) ssid, (char*) password );
  while ( WiFi.status() != WL_CONNECTED ) {}
}

void connectToServer() {
  IPAddress broadcastIp = getBroadcastAddress( WiFi.subnetMask(), WiFi.localIP() );
  Serial.print( "Broadcast IP: " );
  Serial.println( broadcastIp );

  if ( !client.connect( broadcastIp, port ) ) {
    Serial.print( "Failed to Connect. " );
    delay( 1000 );
    Serial.print( "Next try ..." );
  }
  lastResponse = millis();
  connected = true;
}

void initCommunication() {
  
}

void handleCommunication() {
  if ( !connected ) {
    return;
  }
  while ( client.available() ) {
    lastResponse = millis();
    Serial.print( "Got response: " );
    Serial.println( client.readStringUntil('\r') );
  }
  if ( millis() - lastResponse > TIMEOUT ) {
    Serial.println( "Connection Timeout." );
    connected = false;
  }
}
