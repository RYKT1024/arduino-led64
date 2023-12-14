
#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <FastLED.h>
#include <cmath>

CRGB rgb(int g, int r, int b);
CRGB update_brightness(CRGB color, float brightness);
CRGB color_breath(CRGB color, int step, int j);
CRGB color_gradient(CRGB color_from, CRGB color_to, int step, int j);

void led_switch();
void led_commit();
void show_color(CRGB color);

void setup_led();
void loop_led_breath(int color_arr[], float speed, float brightness);
void loop_led_gradient(int color_1_arr[], int color_2_arr[], float speed, float brightness);

#endif
