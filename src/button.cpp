#include <button.h>
#include <Arduino.h>
#include <led.h>
#include <mode.h>

int button_1 = 22;
int button_2 = 23;

volatile bool button_1_flag = false;
volatile int button_1_clicksum = 0;
volatile unsigned long button_1_lasttime = 0;

volatile bool button_2_flag = false;
volatile int button_2_clicksum = 0;
volatile unsigned long button_2_lasttime = 0;

void button_1_handler();
void button_2_handler();

void setup_button() {
  // 初始化引脚模式
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(button_1), button_1_handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(button_2), button_2_handler, FALLING);

  // 初始化串口通信
  // Serial.begin(115200);
  
  button_1_lasttime = 0;
}

// 切换LED下一个板载模式
void button_1_handler() {
  bool status = digitalRead(button_1);
  unsigned long current = millis();

  if(!status) {
    if ((current - button_1_lasttime) > 250) {
      button_1_clicksum ++;
      button_1_flag = true;
      button_1_lasttime = current;

      int selected = mode_switch(-1);
      Serial.print("Onboard Mode: ");
      Serial.println(selected);
    }
  }
}

// 更改LED状态（开/关）
void button_2_handler() {
  bool status = digitalRead(button_2);
  unsigned long current = millis();

  if(!status) {
    if ((current - button_2_lasttime) > 250) {
      button_2_clicksum ++;
      button_2_flag = true;
      button_2_lasttime = current;

      led_switch();
    }
  }
}

void loop_button() {
  // if(button_1_flag) {
  //   // Serial.print("button 1 clicked.");
  //   // Serial.print('x');
  //   // Serial.println(button_1_clicksum);
  //   button_1_flag = false;
  // }
  // else if(button_2_flag) {
  //   // Serial.print("button 2 clicked.");
  //   // Serial.print('x');
  //   // Serial.println(button_2_clicksum);
  //   button_2_flag = false;
  // }
} 
