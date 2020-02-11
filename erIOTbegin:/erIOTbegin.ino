#include "hardware.h"
#include "sensors.h"
#include "config.h"
#include "wifi.h"
#include "webserver.h"
#include "string.h"


struct CONFIG  config;
unsigned long previousMillis = 0;
const long interval = 1000;

void setup() {
  //on appelle la partie setup wifi hadware etc...
  pinMode(RELAY, OUTPUT);
  pinMode(LED_ANT, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  digitalWrite(RELAY, 0);
  digitalWrite(LED_ANT, 1);
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BLUE_LED, 0);

  Serial.begin(115200);

  config.sensorsPeriod = 1000 ;
  strncpy(config.ssid, "GEWIFITP1", 32);
  strncpy(config.passwd, "geiigeii", 64);

  setup_sensors();
  setup_wifi();
  setup_webserver();
}




void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= config.sensorsPeriod) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    loop_sensors();
  }
  loop_webserver();
  loop_wifi();

}
