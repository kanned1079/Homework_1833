#include "LCD.h"
#define uint unsigned int
#define uchar unsigned char

//函数声明
void Delayms(uint xms);	//延时函数
 

/**************************** 延时函数
*****************************/
void Delayms(uint xms)	//i=xms 即延时 i 毫秒
{
  uint I,j; 
  for(I=xms;I>0;I--)
    for(j=587;j>0;j--);

}

/*************************** 主函数
***************************/
void main(void)
{

/*定义显示信息*/
  uchar *mes1 = "WCHSB WCHSB WCHSB";
  uchar *mes2 = "WCHSB WCHSB"; 
  uchar *mes3 = "WCHSB";

  P0DIR = 0XFF; 
  P1DIR = 0XFF;
  ResetLCD(); //复位 LCD 
  initLCDM(); //初始化 LCD 
  ClearRAM(); //请液晶缓存

  delay_us(100);


/*打印刚刚定义的信息*/
 

  Print8(0,0,mes1); 
  Print8(0,2,mes2);  
  Print8(0,4,mes3);
}
