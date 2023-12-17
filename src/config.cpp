#include "config.h"

void BreathConfig::show_mode() {
    Serial.println(mode);
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

const char *BreathConfig::get_json() const {
    std::string result = "{\"mode\":\"" + std::string(mode) + "\", ";
    result += "\"brightness\":" + std::to_string(brightness) + ", ";
    result += "\"speed\":" + std::to_string(speed) + ", ";
    result += "\"color\":[" + std::to_string(color[0]) + ", " + std::to_string(color[1]) + ", " + std::to_string(color[2]) + "]}";
    return result.c_str();
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

const char *GradientConfig::get_json() const {
    std::string result = "{\"mode\":\"" + std::string(mode) + "\", ";
    result += "\"brightness\":" + std::to_string(brightness) + ", ";
    result += "\"speed\":" + std::to_string(speed) + ", ";
    result += "\"color_from\":[" + std::to_string(color_from[0]) + ", " + std::to_string(color_from[1]) + ", " + std::to_string(color_from[2]) + "], ";
    result += "\"color_to\":[" + std::to_string(color_to[0]) + ", " + std::to_string(color_to[1]) + ", " + std::to_string(color_to[2]) + "]}";
    return result.c_str();
}



void StaticConfig::show_mode() {
    Serial.println("Static");
}

void StaticConfig::show_detail() {
    Serial.println("Static Detail:");
    Serial.print("Brightness: ");
    Serial.println(brightness);
    // Serial.print("Colors: ");
    // Serial.print();
}

const char *StaticConfig::get_mode() const {
  return mode;
}

const char *StaticConfig::get_json() const {
    std::string result = "{\"mode\":\"" + std::string(mode) + "\", ";
    result += "\"brightness\":" + std::to_string(brightness) + ", ";
    result += "\"colors\":[";
    for (int i = 0; i < 64; ++i) {
        result += "[" + std::to_string(colors[i][0]) + ", " + std::to_string(colors[i][1]) + ", " + std::to_string(colors[i][2]) + "]";
        if (i < 63) {
            result += ", ";
        }
    }
    result += "]}";
    return result.c_str();
}