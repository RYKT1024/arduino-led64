#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// 基类
class Config {
public:

  virtual void show_mode() = 0; 
  virtual void show_detail() = 0; 
  virtual const char *get_mode() const = 0;
  virtual const char *get_json() const = 0;
};

// 派生类 BreathConfig
class BreathConfig : public Config {
public:
  const char *mode;
  float brightness;
  float speed;
  int color[3];

  void show_mode() override;
  void show_detail() override;
  const char *get_mode() const override;
  const char *get_json() const override;
};

// 派生类 GradientConfig
class GradientConfig : public Config {
public:
  const char *mode;
  float brightness;
  float speed;
  int color_from[3];
  int color_to[3];

  void show_mode() override;
  void show_detail() override;
  const char *get_mode() const override;
  const char *get_json() const override;
};

#endif  
