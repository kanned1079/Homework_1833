#include <ioCC2530.h>
#include "InitUART_Timer.h"	//注意在 option 里设置路径
#include "stdio.h"
/****************************************************************
温度传感器初始化函数
****************************************************************/ 
void initTempSensor(void)
 
{
  DISABLE_ALL_INTERRUPTS();		//关闭所有中断 
  InitClock();	//设置系统主时钟为 32M
  TR0=0X01;	//set '1' to connectthe temperature sensorto the SOC_ADC.
  ATEST=0X01;	// Enablesthe temperature sensor

}
/****************************************************************
读取温度传感器 AD  值函数
****************************************************************/ 
float getTemperature(void)
{

  uint	value;
  ADCCON3	= (0x3E);	//选择 1.25V 为参考电压；12 位分辨率； 对片内温度传感器采样
  ADCCON1 |= 0x30;	//选择 ADC 的启动模式为手动
  ADCCON1 |= 0x40;	//启动 AD 转化
  while(!(ADCCON1 & 0x80));	//等待 AD  转换完成
  value =	ADCL >> 4;	//ADCL  寄存器低 4  位无效
  value |= (((UINT16)ADCH) << 4);
  return (value-1367.5)/4.5-4;	//根据 AD  值，计算出实际的温度,芯片、
//手册有错，温度系数应该是 4.5 /℃
//进行温度校正，这里减去 4℃（不同芯 片根据具体情况校正）
}
/****************************************************************
主函数
****************************************************************/
void main(void)
{

  char I;
  char TempValue[6]; 
  float AvgTemp;
  InitUART0();	//初始化串口
  initTempSensor();	//初始化 ADC 
  while(1)
  {

    AvgTemp = 0;
    for(I = 0 ; I < 64 ; I++)
      {

        AvgTemp += getTemperature();
        AvgTemp=AvgTemp/2;	//每次累加后除 2
      }
/****温度转换成 ascii 码发送****/
    
    UartTX_Send_String("Wuchenghao",10);
    TempValue[0] = (unsigned char)(AvgTemp)/10 + 48;		//十位 
    TempValue[1] = (unsigned char)(AvgTemp)%10 + 48;		//个位 
    TempValue[2] = '.';	//小数点
    TempValue[3] = (unsigned char)(AvgTemp*10)%10+48; //十分位 
    TempValue[4] = (unsigned char)(AvgTemp*100)%10+48; //百分位 
    TempValue[5] = '\0';	//字符串结束符
    UartTX_Send_String( TempValue,6);
    Delayms(2000);	//使用 32M 晶振，故这里 2000 约等于 1S
  }
}
