#ifndef MODE_H
#define MODE_H

#include <Arduino.h>
#include <led.h>
#include <config.h>

void setup_mode();
void loop_mode();

Config **get_onboard();
void set_mode(int onboard, Config *config);
int mode_switch(int select);

#endif