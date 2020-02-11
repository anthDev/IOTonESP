/*
   sensors.cpp

    Created on: 4 mai 2019
        Author: philippe
*/
#include <Arduino.h>
#include "sensors.h"
#include "hardware.h"
#include "config.h"
#include "FS.h"

struct DATA currentData ;
extern struct CONFIG config;



DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

CircularBuffer<DATA, HISTORY_SIZE> buffer; //déclaré et on yajoute à chaque fois la structure DATA
// de la taille de HISTORY_SIZE, soit 10...



void setup_sensors() { // on intialise les camméra pour qu'elles puissent démarer.
  dht.begin();
  Wire.begin();
  lightMeter.begin();

}


// boucle de relève, traitement des datas des capteurs. On utilise currentData.type de capteur.
void loop_sensors() {
  //  currentData.temperature =  dht.readTemperature(0, 0);
  //  currentData.humidity = dht.readHumidity(0);
  //  currentData.light = lightMeter.readLightLevel();
  fake_sensors(); //activation des faux sensors dans la boucle avec acquisition des datas
  buffer.push(currentData); // ajout
  for (int i = 0; i < buffer.size(); i++) {
    /*Serial.print("Donnee numero : ");
      Serial.println(i);
      Serial.println(buffer[i].temperature);*/
    print_sensors(buffer[i]);

  }
  File data;
  data = SPIFFS.open("/sensors.csv", "a");
  if (data) {
    data.printf("%lu, %3.2f,%3.2f,%3.2f \r\n", currentData.timeStamp, currentData.light, currentData.temperature,  currentData.humidity);
  }
  data.flush();
  data.close();
}

void fake_sensors() {
  currentData.temperature = random(190, 240) / 10.0;
  currentData.humidity = random(400, 990) / 10.0;
  currentData.light = random(0, 5000);
  currentData.supplyVoltage = random(110, 144) / 10.0;
  currentData.timeStamp = millis();
}

void print_sensors(struct DATA maData) {
  Serial.print(" Température ");
  Serial.println(maData.temperature);
  Serial.print(" Humidité ");
  Serial.print(maData.humidity);
  Serial.print(" Luminosité ");
  Serial.print(maData.light);
  Serial.print(" Tension ");
  Serial.print(maData.supplyVoltage);
  Serial.println(maData.timeStamp);

}
