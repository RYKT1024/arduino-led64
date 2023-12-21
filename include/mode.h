#ifndef MODE_H
#define MODE_H

#include <Arduino.h>
#include <led.h>
#include <config.h>

void setup_mode();
void loop_mode();

Config **get_onboard();
int get_status();
void set_mode(int onboard, const char *mode, Config *config);
int mode_switch(int select);

#endif