#include "config.h"

void BreathConfig::show_mode() {
    Serial.println("Breath");
}

void BreathConfig::show_detail() {
    Serial.println("Breath Detail:");
    Serial.print("Brightness: ");
    Serial.println(brightness);
    Serial.print("Speed: ");
    Serial.println(speed);
    Serial.print("Color: ");
    Serial.print(color[0]);
    Serial.print(", ");
    Serial.print(color[1]);
    Serial.print(", ");
    Serial.println(color[2]);
}

const char *BreathConfig::get_mode() const {
    return mode;
}



void GradientConfig::show_mode() {
    Serial.println("Gradient");
}

void GradientConfig::show_detail() {
    Serial.println("Gradient Detail:");
    Serial.print("Brightness: ");
    Serial.println(brightness);
    Serial.print("Speed: ");
    Serial.println(speed);
    Serial.print("Color From: ");
    Serial.print(color_from[0]);
    Serial.print(", ");
    Serial.print(color_from[1]);
    Serial.print(", ");
    Serial.println(color_from[2]);
    Serial.print("Color To: ");
    Serial.print(color_to[0]);
    Serial.print(", ");
    Serial.print(color_to[1]);
    Serial.print(", ");
    Serial.println(color_to[2]);
}

const char *GradientConfig::get_mode() const {
  return mode;
}

