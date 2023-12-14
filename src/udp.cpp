#include <udp.h>
#include <Arduino.h>
#include <WiFi.h>  

WiFiUDP Udp;  //声明UDP对象

char incomingPacket[255];  //存储Udp客户端发过来的数据
const char * ssid = "507-Wifi";
const char * password = "123000666";

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

void loop_udp() {
  /*接收发送过来的Udp数据*/
  int Data_length = Udp.parsePacket();  //获取接收的数据的长度
  if (Data_length)                      //如果有数据那么Data_length不为0，无数据Data_length为0
  {
    int len = Udp.read(incomingPacket, 255);  //读取数据，将数据保存在数组incomingPacket中
    if (len > 0)                              //为了避免获取的数据后面乱码做的判断
    {
      incomingPacket[len] = 0;
    }
    Serial.println(incomingPacket);

    /*将接受到的数据发送回去*/
    IPAddress remoteIP = Udp.remoteIP();
    Udp.beginPacket(remoteIP, 6688);  //准备发送数据到目标IP和目标端口
    Udp.print("接收到的数据：");                      //将数据 "接收到的数据：" 放入发送的缓冲区
    Udp.println(incomingPacket);                   //将接收到的数据放入发送的缓冲区
    Udp.endPacket();                                   //向目标IP目标端口发送数据
  }
}
