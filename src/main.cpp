#include <Arduino.h>
#include <led.h>
#include <button.h>

#define DELAY_TIME 10

int green_yellow[] = {120, 240, 0};
int pink_purple[] = {240, 0, 120};
int blue_green[] = {0, 240, 120};

float speed = 0.6;
float brightness = 0.3;

void setup() { 
    setup_led();
    setup_button();
}

void loop() { 
  led_breath(blue_green, speed, brightness);

  button_loop();
  delay(DELAY_TIME);
}