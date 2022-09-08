#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_0	
#define KEY1 P0_4	

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
  P1DIR |= 0x01;
  LED1 = 1;	
}

void InitKey()
{
  P0SEL &= ~0X10;	
  P0DIR &= ~0X10;	
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
return 0;	//�ް�������
}

void main(void)
{
  InitLed();	//���ó�ʼ������ 
  InitKey();
  while(1)
  {
    if(KeyScan())	//�����ı� LED ״̬ 
    LED1=~LED1;
  }
}
