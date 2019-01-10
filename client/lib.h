#include <WiFi.h>
#include <WiFiUdp.h>



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

void connectToServer( int broadcastPort, int port ) {
  WiFiUDP broadcastContact;
  WiFiUDP broadcastReceiver;

  // calculating the broadcast address
  IPAddress broadcastIp = getBroadcastAddress( WiFi.subnetMask(), WiFi.localIP() );

  // scan for picroft
  broadcastReceiver.begin( port );

  Serial.println( "scanning ..." );
  broadcastContact.beginPacket( broadcastIp, broadcastPort );
  broadcastContact.write( "new microcroft" );
  broadcastContact.endPacket();

  Serial.println( "Waiting for response..." );  
  broadcastReceiver.parsePacket(); // wait for response
  // TODO: do something with the packet
  broadcastContact.stop();
  broadcastReceiver.stop();

  // connect to picroft
  IPAddress remoteAddress = broadcastReceiver.remoteIP();
  while ( !client.connect( remoteAddress, port ) ) {
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
