================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC采集通过TIM触发采集并通过DMA传输的模式，PA4为模拟输入，每隔1s会从
串口打印当前的电压值。

Function descriptions:
This sample demonstrates ADC data acquisition using TIM-triggered sampling 
and DMA transfer mode. PA4 is an analog input, and the current voltage value 
will be printed via the serial port every 1s.
================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F003_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 定时器每隔1s触发一次ADC采样；
3. 每完成一次采样，打印一次PA4上的采样值。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The timer triggers ADC sampling every 1s.
3.After each sampling is completed, the sampled value on PA4 will be 
printed via the serial port.
================================================================================
注意事项：
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板        USB转TTL模块
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART配置为波特率115200，数据位8，停止位1，校验位None
@PrintfConfigEnd

Notes:
Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART is configured as BaudRate 115200, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
================================================================================