#include <ioCC2530.h>
#define L1 P1_0
#define L2 P1_1

#define R1 P1_3

void delay(unsigned int xms) 
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=1200;y>0;y--);
}

main()
{
  P1DIR |= 0x0b;
  L1 = 1;

  L2 = 1;

  R1 = 0;
  while(1)
  {
    delay(1000);
    L1=0;
    L2=1;
    R1 =~ R1; 
    delay(1000);
    L1=1;
    L2=0;
    R1 =~ R1; 
  }
}

