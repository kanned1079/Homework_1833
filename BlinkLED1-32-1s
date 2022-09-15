#include <ioCC2530.h>
#define LED1 P1_0
unsigned int count;
void initial_t1()
{
  T1IE = 1;
  T1CTL = 0x09; //8分频0x05用60
  TIMIF |= 0x40;
  EA = 1;
}
#pragma vector = T1_VECTOR
__interrupt void T1_ISR(void)
{
  IRCON = 0x00;
  if(count>15)
  {
   count = 0x00;
   LED1 = !LED1;
  }
  else
  {
    count++;
  }
}
void main(void)
{
  
  
  CLKCONCMD &= ~0x7f;
  while(CLKCONCMD & 0x40);
  initial_t1();
  P1SEL &= ~0x01;
  P1DIR |= 0x01;
  LED1 = 0;
  while(1);
}
