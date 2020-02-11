/*
   webserver.cpp

    Created on: 4 mai 2019
        Author: philippe
*/
#include "sensors.h"
#include "config.h"
#include "webserver.h"




extern struct CONFIG config;
extern struct DATA currentData ;
//extern CircularBuffer<struct DATA, HISTORY_SIZE > dataBuffer;
ESP8266WebServer server(80);


void setup_webserver() { // page web intiale...

  SPIFFS.begin();
  server.onNotFound([]() {                              // If the client requests any URI
    if (!handleFileRead(server.uri()))                  // send it if it exists
      server.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  //  server.on("/", handleRoot);
  //  server.on("/execute", Execute);
  //  server.on("/inline", []() {
  //    server.send(200, "text/plain", "this works as well");
  //  });

  //server.onNotFound(handleNotFound);
  //server.on("/",handleRoot);
  server.begin();
  Serial.println("HTTP server started");

  //  String mess = "Luminosite : " + String(currentData.light);
  //  String mess1 = "Temperature : " + String(currentData.temperature);
  //  String mess2 = "Humidite : " + String(currentData.humidity);
  //  server.send ( 200, "text/plain", mess);
  //  server.send ( 200, "text/plain", mess1);
  //  server.send ( 200, "text/plain", mess2);
  server.on("/getUptime", handleUptime);
  server.on("/setLED", setLed);
  server.on("/getDataTemp", handleDataTemp);
  server.on("/getDataHum", handleDataHum);
  server.on("/getDataLum", handleDataLum);
}

void loop_webserver() {

  server.handleClient();


}


void handleUptime() {
  String uptime = String(millis() / 1000);
  server.send(200, "text/plain", uptime);
}

void handleDataTemp() {
  String dataTemp;
  if (currentData.temperature != 0) {

    dataTemp = "Capteur temperature allume vaut : " + String(currentData.temperature);
  }
  if (currentData.temperature == 0) {

    dataTemp = "Capteur temperature allume il fait 0°C";
  }
  server.send(200, "text/plain", dataTemp);
}

void handleDataHum() {
  String dataHum;
  if (currentData.humidity != 0) {

    dataHum = "Capteur humidité allume vaut : " + String(currentData.humidity);
  }

  server.send(200, "text/plain", dataHum);
}

void handleDataLum () {
  String dataLum;
  if (currentData.light != 0) {

    dataLum = "Capteur lumiere allume vaut : " + String(currentData.light);
  }

  server.send(200, "text/plain", dataLum);
}
void handleRoot() { // page web
  //  String mess = "Luminosite : " + String(currentData.light);
  //  String mess1 = "Temperature : " + String(currentData.temperature);
  //  String mess2 = "Humidite : " + String(currentData.humidity);
  //  server.send ( 200, "text/plain", mess);
  //  server.send ( 200, "text/plain", mess1);
  //  server.send ( 200, "text/plain", mess2);


}

void handleNotFound() { // message web à afficher lorsque la demande n'est pas trouvé...

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";


}

String getContentType(String filename) { // convert the file extension to the MIME type
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".csv")) return "text/csv";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  return "text/plain";
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";         // If a folder is requested, send the index file
  String contentType = getContentType(path);            // Get the MIME type
  if (SPIFFS.exists(path)) {                            // If the file exists
    File file = SPIFFS.open(path, "r");                 // Open it
    size_t sent = server.streamFile(file, contentType); // And send it to the client
    file.close();                                       // Then close the file again
    return true;
  }
  Serial.println("\tFile Not Found");
  return false;                                         // If the file doesn't exist, return false
}
// c'est une page web en developpement...


// fonction permettant d'executer les requettes url qui commande le relay et la led à l'aide d'une valeur booléene. en intérogant avec "?"...

void setLed() {
  if (server.arg(0) == "0") {
    digitalWrite(LED_ANT, 0);
  }
  if (server.arg(0) == "1") {
    digitalWrite(LED_ANT, 1);
  }
  int val = digitalRead(LED_ANT);
  server.send(200, "text/plain", String(val) );
}

void Execute() {
  if (server.argName(0) == "relay") {   //relay=[on|off|tog]
    if (server.arg(0) == "off") {

      digitalWrite(RELAY, 1);

    } else {
      if (server.arg(0) == "on") {

        digitalWrite(RELAY, 0);

      }

    }
  }

  if (server.argName(0) == "led") {   //relay=[on|off|tog]
    if (server.arg(0) == "off") {

      digitalWrite(RELAY, 0);

    } else {
      if (server.arg(0) == "on") {

        digitalWrite(RELAY, 1);


      }

    }
  }
  int a = digitalRead(RELAY);
  server.send(200, "text/plain", "valeur du relay : " + String(a)); // code permettant de revoyer la valeur actuelle du relay en fonction de la commande ecrite dans l'url. En developpement également...

}
