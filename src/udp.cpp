#include <udp.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <config.h>
#include <cstring>
#include <mode.h>

WiFiUDP Udp;  //声明UDP对象

char incomingPacket[2048];  //存储Udp客户端发过来的数据
const char *ssid = "507-Wifi";
const char *password = "123000666";

IPAddress remoteIP; //存储服务器IP

void setup_udp() {
  Serial.begin(115200);                 //开启串口，波特率为115200

  WiFi.begin(ssid, password);
  Serial.print("Connect to:");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Succeed");
  Serial.print("Your IP:");
  Serial.println(WiFi.localIP());

  Udp.begin(1122);                //启动UDP监听这个端口
}

// json: {"mode":"breath", "config":{"onboard":0, "brightness":0.4, "speed":0.8, "color":[255, 0, 120]}}
void handler_breath(StaticJsonDocument<2048> doc) {
  BreathConfig config;
  config.mode = doc["mode"];
  config.brightness = doc["config"]["brightness"];
  config.speed = doc["config"]["speed"];
  config.color[0] = doc["config"]["color"][0];
  config.color[1] = doc["config"]["color"][1];
  config.color[2] = doc["config"]["color"][2];
  // config.show_mode();

  int onboard = doc["config"]["onboard"];
  set_mode(onboard, &config);
}

// json: {"mode":"gradient", "config":{"onboard":0, "brightness":0.4, "speed":0.8, "color_from":[255, 0, 120], "color_to":[0, 255, 0]}}
void handler_gradient(StaticJsonDocument<2048> doc) {
  GradientConfig config;
  config.mode = doc["mode"];
  config.brightness = doc["config"]["brightness"];
  config.speed = doc["config"]["speed"];
  config.color_from[0] = doc["config"]["color_from"][0];
  config.color_from[1] = doc["config"]["color_from"][1];
  config.color_from[2] = doc["config"]["color_from"][2];
  config.color_to[0] = doc["config"]["color_to"][0];
  config.color_to[1] = doc["config"]["color_to"][1];
  config.color_to[2] = doc["config"]["color_to"][2];
  // config.show_detail();

  int onboard = doc["config"]["onboard"];
  set_mode(onboard, &config);
}

void get_handler_onboard() {
  Config **config = get_onboard();

  Udp.beginPacket(remoteIP, 6688);  //准备发送数据到目标IP和目标端口
  Udp.print('{');
  for(int i=0; i<5; i++) {
    Udp.printf("\"%d\":", i);
    Udp.print(config[i]->get_json());
    if(i<4)
      Udp.print(", ");
  } 
  Udp.println('}');
  Udp.endPacket();                                   //向目标IP目标端口发送数据
  
}

void loop_udp() {
  /*接收发送过来的Udp数据*/
  int Data_length = Udp.parsePacket();  //获取接收的数据的长度
  if (Data_length)                      //如果有数据那么Data_length不为0，无数据Data_length为0
  {
    int len = Udp.read(incomingPacket, 2048);  //读取数据，将数据保存在数组incomingPacket中
    if (len > 0)                              //为了避免获取的数据后面乱码做的判断
    {
      remoteIP = Udp.remoteIP();
      incomingPacket[len] = 0;

      // 删除最前面和最后面的引号
      String cleanedData = incomingPacket;
      cleanedData.trim();

      // 解析JSON数据
      StaticJsonDocument<2048> doc; // 适当调整文档大小
      DeserializationError error = deserializeJson(doc, cleanedData.c_str());

      if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.c_str());
      } else {
        // 从JSON文档中提取数据
        const char *mode = doc["mode"];
        if(!strcmp(mode, "get_onboard")) {
          get_handler_onboard();
        }
        else if(!strcmp(mode, "breath")) {
          handler_breath(doc);
        } 
        else if(!strcmp(mode, "gradient")) {
          handler_gradient(doc);
        }
      }
    }
  }
}
