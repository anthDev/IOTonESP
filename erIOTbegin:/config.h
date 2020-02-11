/*
   config.h

    Created on: 4 mai 2019
        Author: philippe
*/

#ifndef CONFIG_H_
#define CONFIG_H_
#include <IPAddress.h>
#define HISTORY_SIZE 10 // number of values in the circular buffer

struct CONFIG {
  char ssid[32] ; // ssid of wifi network to connect to
  char passwd[64]  ;
  char myhostname[32] ; // the name of the ESP
  IPAddress mqttServerIp ;
  unsigned long sensorsPeriod ; // milliseconds
} ;




#endif /* CONFIG_H_ */
//
//structure ---> toto
//
//toto.passwd
