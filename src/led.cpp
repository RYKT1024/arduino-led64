#include <led.h>
#include <Arduino.h>
#include <FastLED.h>
#include <cmath>

#define NUM_LEDS 64
#define DATA_PIN 32

CRGB leds[NUM_LEDS];
bool led_status = true;

void setup_led() {
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  
  // Serial.begin(115200);
}

void show_color(CRGB color) {
  Serial.print(color.g);
  Serial.print(',');
  Serial.print(color.r);
  Serial.print(',');
  Serial.println(color.b);
}

void led_switch() {
  led_status = !led_status;
}

CRGB rgb(int g, int r, int b) {
  return CRGB(r, g, b);
}

CRGB update_brightness(CRGB color, float brightness) {
  int r = static_cast<int>(color.g * brightness);
  int g = static_cast<int>(color.r * brightness);
  int b = static_cast<int>(color.b * brightness);

  return rgb(r, g, b);
}

CRGB color_breath(CRGB color, int step, int j) {
  int origin_r = color.g;
  int origin_g = color.r;
  int origin_b = color.b;
  float low = 0.05;
  float high = 1 - low;

  float now = fabs((j % (step*2) - step) / static_cast<float>(step));
  int r = static_cast<int>(origin_r * (now * high + low));
  int g = static_cast<int>(origin_g * (now * high + low));
  int b = static_cast<int>(origin_b * (now * high + low));

  return rgb(r,g,b);
}

/**
 * color_arr  ：颜色数组，顺序为RGB
 * speed      ：每秒变化的百分比
 * brightness ：0到1之间的值
*/
void led_breath(int color_arr[], float speed, float brightness) {
  CRGB color_origin = rgb(color_arr[0], color_arr[1], color_arr[2]);
  static int j = 0;
  static int step = static_cast<int>(100 / speed);
  CRGB color = color_breath(color_origin, step, j);
  color = update_brightness(color, brightness);

  // show_color(color);
  fill_solid(leds, NUM_LEDS, color);
  led_commit();
  j++;
}

void led_commit(){
  if (!led_status) {
    fill_solid(leds, NUM_LEDS, rgb(0, 0, 0));
  }
  FastLED.show();
}