#include <Arduino.h>
#include <button.h>
#include <udp.h>
#include <mode.h>
#include <led.h>

#define DELAY_TIME 10

bool flag = true;

void setup() { 
    setup_mode();
    setup_button();
    setup_udp();
}

void loop() { 
  loop_mode();
  loop_button();
  loop_udp();

  delay(DELAY_TIME);
}