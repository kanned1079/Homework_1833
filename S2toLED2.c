#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_0
#define LED2 P1_1
#define KEY1 P0_5	

void Delayms(uint);	
void KeyInit();	
uchar KeyScan();	

void Delayms(uint xms)	
{
  uint i,j; 
  for(i=xms;i>0;i--)
    for(j=587;j>0;j--);
}

void InitLed(void)
{
  P1DIR |= 0x03;
  LED1 = 1;	
}

void InitKey()
{
  P0SEL &= ~0X20;	
  P0DIR &= ~0X20;	
}

uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);  
    if(KEY1==0)
    {
      while(!KEY1);	
      return 1;	
    }
  }
return 0;	//无按键按下
}

void main(void)
{
  InitLed();	//调用初始化函数 
  InitKey();
  while(1)
  {
    if(KeyScan())	//按键改变 LED 状态 
    LED2=~LED2;
  }
}
