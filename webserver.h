/*
   webserver.h

    Created on: 4 mai 2019
        Author: philippe
*/

#ifndef WEBSERVER_H_
#define WEBSERVER_H_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "hardware.h"
#include "FS.h"

void setup_webserver();
void loop_webserver();
void handleRoot();
void handleNotFound();
//String getPage();
void Execute();
void handleUptime();
void setLed();
void handleDataTemp();
void handleDataHum();
void handleDataLum();

String getContentType(String filename); // convert the file extension to the MIME type
bool handleFileRead(String path);

#endif /* WEBSERVER_H_ */
