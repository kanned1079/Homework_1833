#include<ioCC2530.h>
char data[]="What is your name?\n";
char name_string[20];
unsigned char temp,RX_flag,counter=0;

void Delayms(unsigned int i)
{
  unsigned int k,j;
  for(k=0;k<i;k++)
    for(j=0;j<500;j++);
}

void initial_usart()
{
  CLKCONCMD&=~0X7F;
  while(CLKCONSTA&0X40);
  CLKCONCMD&=~0X47;
  PERCFG=0X00;
  P0SEL|=0X3C;
  P2DIR&=~0XC0;
  U0CSR|=0XC0;
  U0GCR=9;
  U0BAUD=59;
  URX0IF=0;
  IEN0=0X84;
}

void uart_tx_string(char *data_tx,int len)
{
  
    unsigned int j;
    for(j=0;j<len;j++)
    {
      U0DBUF=*data_tx++;
      while(UTX0IF==0);
      UTX0IF=0;
    }
  
}

void main(void)
{
  initial_usart();
  uart_tx_string(data,sizeof(data));
  while(1)
  {
    if(RX_flag==1)
    {
      RX_flag=0;
        if(temp!='#')
          name_string[counter++]=temp;
        else
        {
          U0CSR &=~0x40;
          uart_tx_string("Hello ",sizeof("Hello "));
          Delayms(1000);
          uart_tx_string(name_string,counter);
          counter=0;
          U0CSR |= 0x40;
        }
    }
  }
}
               
#pragma vector=URX0_VECTOR
__interrupt void UART0_RX_ISR(void)
{
  URX0IF=0;
  temp=U0DBUF;
  RX_flag=1;
}
