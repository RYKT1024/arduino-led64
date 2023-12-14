#include <button.h>
#include <Arduino.h>
#include <led.h>

int button_1 = 22;
int button_2 = 23;

int click_status_1 = 0;
int click_sum_1 = 0;

int click_status_2 = 0;
int click_sum_2 = 0;

void setup_button() {
  // 初始化引脚模式
  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);

  // 初始化串口通信
  Serial.begin(115200);
  
  Serial.println("你好！");
}

void button_1_handler() {
  click_sum_1 ++;
  Serial.print("button_1 is clicked. x");
  Serial.println(click_sum_1);
}

void button_2_handler() {
  click_sum_2 ++;
  led_switch();
  Serial.print("button_2 is clicked. x");
  Serial.println(click_sum_2);
}

void loop_button() {
  // 按钮消抖
  if (!digitalRead(button_1)) {
    click_status_2 = 0;
    delay(10);
    if (!digitalRead(button_1) && !click_status_1) { 
      button_1_handler();
      click_status_1 = 1;
    }
  } else if (!digitalRead(button_2)) {
    click_status_1 = 0;
    delay(10);
    if (!digitalRead(button_2) && !click_status_2) { 
      button_2_handler();
      click_status_2 = 1;
    }
  } else {
    click_status_1 = 0;
    click_status_2 = 0;
  }
} 
