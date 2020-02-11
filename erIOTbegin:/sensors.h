/*
   sensors.h

    Created on: 4 mai 2019
        Author: philippe
*/

#ifndef SENSORS_H_
#define SENSORS_H_

#include <Arduino.h>
#include <DHT.h>
#include <config.h>
#include <Wire.h>
#include <BH1750.h>
#include <CircularBuffer.h>


//Lorsque vous déclarez votre tampon,
//vous devez préciser le type de données qu'il doit
//traiter et la capacité du tampon : ces deux paramètres influenceront
//la mémoire consommée par le tampon.

struct DATA {
  float temperature ; // temperature °C
  float humidity ;// humidity %
  float light ;//ambient light lux
  float supplyVoltage ;// Volt
  uint32_t timeStamp ; // millis at time of reading
} ;

//partie capteur virtuels en cas de panne...
#define DHTTYPE DHT22
void setup_sensors();
void loop_sensors();
void fake_sensors();
void print_sensors(struct DATA maData);


#endif /* SENSORS_H_ */
