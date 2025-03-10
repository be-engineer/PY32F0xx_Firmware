================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了主机I2C、从机I2C通过轮询方式进行通讯，当按下从机单板的用户按键，再
按下主机单板的用户按键后，主机I2C向从机I2C发送"LED ON"数据。当主机I2C成功发送数
据，从机I2C成功接收数据时，主机单板和从机单板LED灯分别亮起。

Function descriptions:
This sample demonstrates I2C communication between a master and a slave 
using polling. When the user button on the slave board is pressed, 
followed by pressing the user button on the master board, the master 
I2C sends the "LED ON" data to the slave I2C. When the master successfully 
sends the data and the slave successfully receives the data, the LEDs on 
the master and slave boards will light up.
================================================================================
测试环境：
测试用板：PY32F002A_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F002A_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 注释掉main.h的宏定义“#define SLAVE_BOARD”，编译下载程序到MCU(为主机)，并运行；
   打开main.h的宏定义“#define SLAVE_BOARD”，编译下载程序到MCU(为从机)，并运行；
2. 先复位从机，然后再复位主机；
3. 复位完成后，先按下从机单板的用户按键，再按主机单板的用户按键，主从开始通讯；
4. 当主机I2C成功发送数据，从机I2C成功接收数据时，主机单板和从机单板LED灯分别亮起；
   否则，LED灯处于闪烁状态。

Example execution steps:
1.Comment out the macro definition "#define SLAVE_BOARD" in the main.h file, 
then compile and download the program to the MCU (as the master), and run it.
2.Uncomment the macro definition "#define SLAVE_BOARD" in the main.h file, 
then compile and download the program to the MCU (as the slave), and run it.
3.Reset the slave first, then reset the master.
4.After the reset is complete, press the user button on the slave board, 
followed by pressing the user button on the master board to initiate the 
communication between the master and slave.
5.When the master successfully sends the data and the slave successfully 
receives the data, the LEDs on the master and slave boards will light up; 
otherwise, the LEDs will blink.
================================================================================
注意事项：
PA3     ------> I2C1_SCL
PA2     ------> I2C1_SDA 

Notes:
PA3     ------> I2C1_SCL
PA2     ------> I2C1_SDA 
================================================================================