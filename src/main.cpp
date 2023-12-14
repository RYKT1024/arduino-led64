#include <Arduino.h>
#include <led.h>
#include <button.h>
#include <udp.h>

#define DELAY_TIME 10

int green_yellow[] = {120, 240, 0};
int pink_purple[] = {240, 0, 120};
int blue_green[] = {0, 240, 120};

float speed = 0.2;
float brightness = 0.2;

void setup() { 
    setup_led();
    setup_button();
    setup_udp();
}

void loop() { 

  loop_led_gradient(green_yellow, blue_green, speed, brightness);
  loop_button();
  loop_udp();

  delay(DELAY_TIME);
}