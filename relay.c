#include <ioCC2530.h>
#define R1 P1_3
void delay(unsigned int xms) 
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=1200;y>0;y--);
}

main()
{
  P1DIR |= 0x08;
  R1 = 0;
  while(1)
  {
    delay(500);
    R1 =~ R1; 
  }
}

