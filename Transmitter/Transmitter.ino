#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

  WiFiUDP UDP;
  
  #define WIFI_SSID "Offline"
  #define WIFI_PASS "pretorianec2020"  
  #define UDP_PORT 8266
  
  char packet[255];
  char mas [255];  
  String str;
  
void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {delay(500);}
  // Serial.println("Connected");  
  UDP.begin(UDP_PORT);
  Serial.printf("IP %s, port %d\n", WiFi.localIP().toString().c_str(), UDP_PORT);
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
 
void loop() {
  
void serialEvent();   

  int packetSize = UDP.parsePacket();
  if (packetSize) {
    int len = UDP.read(packet, 255);
    if (len > 0){ packet[len] = 0;} 
  }
    if (packet!=0){Serial.print(packet);}
    for (int k; k<255; k++) {packet[k]=0;}
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    str += inChar;
    if (inChar == '\r') {
      str.toCharArray(mas, 255);
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      UDP.write(mas);
      UDP.endPacket();
      // Serial.println(str);
      str="";}
    }
  }
