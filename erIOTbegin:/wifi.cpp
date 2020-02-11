/*
   wifi.cpp

    Created on: 4 mai 2019
        Author: philippe
*/




#include "wifi.h"
#include "config.h"
extern struct CONFIG config;
String nomMdns, mac;

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(config.ssid, config.passwd);


  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("#Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("#IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());
  Serial.print("MAC: ");
  mac = WiFi.macAddress();
  nomMdns = "geii" + String(mac[12]) + String(mac[13]) + String(mac[15]) + String(mac[16]);


  if (MDNS.begin(nomMdns.c_str())) {
    Serial.println("#MDNS responder started");
    Serial.println(nomMdns);
  }
}



void loop_wifi() {
  MDNS.update();
}
