#include <ioCC2530.h>
#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_0
#define LED2 P1_1

void Delayms(uint xms);
void InitLed(void);

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
  LED2 = 1;
}

void Init_Watchdog(void)
{
  WDCTL = 0x00;
  WDCTL |= 0x08;
}

void FeetDog(void)
{
  WDCTL = 0xa0;
  WDCTL = 0x50;
}

void main(void)
{
  InitLed();
  Init_Watchdog();
  LED1=1;
  while(1)
  {
    LED2 =~ LED2;
    Delayms(300);
    LED1 = 0;
    //FeetDog();
  }
}
