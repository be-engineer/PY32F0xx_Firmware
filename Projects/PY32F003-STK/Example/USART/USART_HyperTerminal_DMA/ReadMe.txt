================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了USART的DMA方式发送和接收数据，USART配置为115200，数据位8，停止位1，
校验位None,下载并运行程序后，通过上位机下发12个数据，例如0x1~0xC,则，MCU会把
接收到的数据再次发送。

================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20

================================================================================
使用步骤：
1. 编译并下载程序到MCU；
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA0(TX) --> RX
PA1(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为115200；
4. 上位机发送12个数据，MCU会反馈同样的12个数据给上位机

================================================================================
注意事项：

================================================================================