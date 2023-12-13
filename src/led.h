
#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>
#include <cmath>

CRGB rgb(int g, int r, int b);
CRGB update_brightness(CRGB color, float brightness);
CRGB color_breath(CRGB color, int step, int j);

void setup_led();
void led_switch();
void led_commit();
void show_color(CRGB color);
void led_breath(int color_arr[], float speed, float brightness);

#endif
