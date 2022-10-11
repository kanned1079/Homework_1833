#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char

#define UINT8 unsigned char
#define UINT16 unsigned int
#define UINT32 unsigned long

//定义控制 LED 灯和按键的端口
#define LED2 P1_1 //定义 LED2 为 P11 口控制
#define KEY1 P0_5

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

/*****************************************
//初始化 Sleep Timer （设定后经过指定时间自行唤醒）
*****************************************/
void Init_SLEEP_TIMER(void)
{
  ST2 = 0X00;
  ST1 = 0X0F;
  ST0 = 0X0F;
  EA = 1; //开中断
  STIE = 1; //SleepTimerinterrupt enable
  STIF = 0; //SleepTimerinterrupt flag 还没处理的
}

/***************************************************************
设置睡眠时间
***************************************************************/
void Set_ST_Period(uint sec)
{
  UINT32 sleepTimer = 0;
  sleepTimer |= ST0;
  sleepTimer |= (UINT32)ST1 << 8;
  sleepTimer |= (UINT32)ST2 << 16;
  sleepTimer += ((UINT32)sec * (UINT32)32768);//低频晶振 PM2 模式
  ST2 = (UINT8)(sleepTimer >> 16);
  ST1 = (UINT8)(sleepTimer >> 8);
  ST0 = (UINT8) sleepTimer;
}

/***************************
//主函数
***************************/
void main(void)
{
  uchar i;
  InitLed(); //调用初始化函数
  Init_SLEEP_TIMER(); //初始化 SLEEPTIMER
  while(1)
  {
    for(i=0;i<6;i++) //闪烁 3 下
    {
      LED2=~LED2;
      Delayms(200);
    }
  Set_ST_Period(3); //重新进入睡眠模式
  SysPowerMode(2); //进入 PM2 低频晶振模式
  }
}
//睡眠中断唤醒
#pragma vector = ST_VECTOR
__interrupt void ST_ISR(void)
{
  STIF = 0; //清标志位
  SysPowerMode(4); //进入正常工作模式
}
