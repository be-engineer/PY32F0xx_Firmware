================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本样例主要读取DBGMCU->IDCODE寄存器和UID的值,并通过串口打印出来。

Function descriptions:
This sample mainly reads the values of the DBGMCU->IDCODE register and UID, and
prints them out via the serial port.
================================================================================
测试环境：
测试用板：PY32F030_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F030_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 串口依次打印Device ID,Revision ID,X and Y coordinates,Water NB,Lot Nb的值。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The serial port will print the values of Device ID, Revision ID, X and Y
coordinates, Water NB, and Lot Nb in sequence.
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