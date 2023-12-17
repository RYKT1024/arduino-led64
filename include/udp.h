#ifndef UDP_H
#define UDP_H

#include <Arduino.h>
#include <WiFi.h>  
#include <ArduinoJson.h>
#include <cstring>
#include <config.h>
#include <mode.h>
#include <led.h>

void setup_udp();
void loop_udp();

void get_handler_onboard();

void handler_breath(StaticJsonDocument<2048> doc);
void handler_gradient(StaticJsonDocument<2048> doc);

#endif