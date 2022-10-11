/**********************************************
程序描述：LED2 闪烁 5 次后进入睡眠状态，通
 过按下按键 S1 产生外部中断进行唤
 醒，重新进入工作模式。
***********************************************/

#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char

//定义控制 LED 灯和按键的端口
#define LED2 P1_1 //定义 LED2 为 P11 口控制
#define KEY1 P0_4

//函数声明
void Delayms(uint); //延时函数
void InitLed(void); //初始化 P1 口
void SysPowerMode(uchar sel); //系统工作模式

/****************************
 延时函数
*****************************/
void Delayms(uint xms) //i=xms 即延时 i 毫秒
{
  uint i,j;
  for(i=xms;i>0;i--)
  for(j=587;j>0;j--);
}

/****************************
//初始化程序
*****************************/
void InitLed(void)
{
  P1DIR |= 0x02; //P1_1 定义为输出
  LED2 = 1; //LED2 灯熄灭
  P0INP &= ~0X10; //设置 P0 口输入电路模式为上拉/ 下拉
  P0IEN |= 0X10; //P01 设置为中断方式
  PICTL |= 0X10; // 下降沿触发
}
/***************************************************************
系统工作模式选择函数
* para1 0 1 2 3
* mode PM0 PM1 PM2 PM3
***************************************************************/
void SysPowerMode(uchar mode)
{
  uchar I,j;
  I = mode;
  if(mode<4)
  {
    SLEEPCMD |= I; // 设置系统睡眠模式
    for(j=0;j<4;j++);
    PCON = 0x01; // 进入睡眠模式 ,通过中断打断
  }
  else
  {
    PCON = 0x00; // 系统唤醒 ，通过中断打断
  }
}

/***************************
 主函数
***************************/
void main(void)
{
  uchar count = 0;
  InitLed(); //调用初始化函数
  IEN1 |= 0X20; //开 P0 口总中断
  P0IFG |= 0x00; //清中断标志
  EA = 1;
  while(1)
  {
    LED2=~LED2;
    if(++count>=10)
    {
      count=0;
      SysPowerMode(3); //5 次闪烁后进入睡眠状态 PM3,
    //等待按键 S1 中断唤醒
    }
    Delayms(500);
  }
}

/*****************************************
 中断处理函数-系统唤醒
*****************************************/
#pragma vector = P0INT_VECTOR
__interrupt void P0_ISR(void)
{
  if(P0IFG>0)
  {
    P0IFG = 0; //清标志位
  }
  P0IF = 0;
  SysPowerMode(4); //正常工作模式
}
