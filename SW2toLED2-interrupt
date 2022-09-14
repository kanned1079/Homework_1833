#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_1	
#define KEY1 P0_5	

void Delayms(uint);
void InitLed(void);
void KeyInit();	
uchar KeyValue=0;
 


void Delayms(uint xms)	
{
  uint i,j; 
  for(i=xms;i>0;i--)
    for(j=587;j>0;j--);

}
void InitLed(void)
{

  
  P1DIR |= 0x02; 
  LED1 = 1;	
}

void InitKey()
{

  P0IEN |= 0X20;	
  PICTL |= 0X20;	
  IEN1	|= 0X20;		
  P0IFG &= ~0x20;			
  EA = 1;	
}


#pragma vector = P0INT_VECTOR	
  __interrupt void P0_ISR(void)
{
  Delayms(6);	
  if(KEY1==0)
  {
    LED1=~LED1;	
    P0IFG &= ~0x20;	
    P0IF = 0;	
  } 
}
void main(void)
{
  InitLed();	
  InitKey();
  while(1);	
}
