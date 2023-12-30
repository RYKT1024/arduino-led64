# arduino-led64

### 开发平台

- Arduino (PlatformIO IDE)	

- Esp32

### 引脚连接

- VIN - V+	LED供电
- GND - V-       LED接地
- D32 - IN        LED数据

- D22                按钮1 - 切换模式

- D23                 按钮2 - 显示开关

### 功能结构

在本项目中，硬件端设计结构如下：

- LED显示
- LED模式缓存
- 按钮中断控制
- UDP数据包处理
  - 接收与解析
  - 打包与发送

基于以上设计，代码结构如下：

- main.cpp	主函数入口，初始化时钟
- led.cpp            处理LED灯阵不同模式的显示
- mode.cpp       管理LED显示模式的缓存以及模式变更
- config.cpp       定义显示模式类及类方法
- button.cpp      设置并处理按钮中断
- udp.cpp           处理json格式UDP数据包的接收与解析,打包与发送
