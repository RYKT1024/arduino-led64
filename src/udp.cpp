#include <udp.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <cstring>

WiFiUDP Udp;  //声明UDP对象

char incomingPacket[2048];  //存储Udp客户端发过来的数据
const char *ssid = "507-Wifi";
const char *password = "123000666";

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

void handler_breath(StaticJsonDocument<2048> doc) {
  const char *mode = "breath";
  float brightness = doc["config"]["brightness"];
  float speed = doc["config"]["speed"];
  int color[3] = {doc["config"]["color"][0], doc["config"]["color"][1], doc["config"]["color"][2]};
  
}

void handler_gradient(StaticJsonDocument<2048> doc) {
  const char *mode = "gradient";
  float brightness = doc["config"]["brightness"];
  float speed = doc["config"]["speed"];
  int color_from[3] = {doc["config"]["color_from"][0], doc["config"]["color_from"][1], doc["config"]["color_from"][2]};
  int color_to[3] = {doc["config"]["color_to"][0], doc["config"]["color_to"][1], doc["config"]["color_to"][2]};
}

void loop_udp() {
  /*接收发送过来的Udp数据*/
  int Data_length = Udp.parsePacket();  //获取接收的数据的长度
  if (Data_length)                      //如果有数据那么Data_length不为0，无数据Data_length为0
  {
    int len = Udp.read(incomingPacket, 2048);  //读取数据，将数据保存在数组incomingPacket中
    if (len > 0)                              //为了避免获取的数据后面乱码做的判断
    {
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
        if(!strcmp(mode, "breath")){
          handler_breath(doc);
        } 
        else if(!strcmp(mode, "gradient")) {
          handler_gradient(doc);
        }
      }
    }
  }
}
