#include <ioCC2530.h>
#include <string.h>

#define uint unsigned int
#define uchar unsigned char

#define LED1 P1_0	
#define LED2 P1_1

void Delayms(uint xms);		//延时函数
void InitLed(void);		//初始化P1口
void InitUart();              //初始化串口
void Uart_Send_String(char *Data,int len);

char Rxdata[50];
uchar RXTXflag = 1; 
char temp; 
uchar  datanumber = 0;

void Delayms(uint xms)   
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
} 

void InitLed(void)
{
	P1DIR |= 0x03; //P1_0、P1_1定义为输出
	LED1 = 1;       //LED1灯熄灭
        LED2=1;    
}

void InitUart()
{
    CLKCONCMD &= ~0x40; // 设置系统时钟源为 32MHZ晶振
    while(CLKCONSTA & 0x40);                     // 等待晶振稳定 
    CLKCONCMD &= ~0x47;                          // 设置系统主时钟频率为 32MHZ

    PERCFG = 0x00;        //位置1 P0口 
    P0SEL = 0x3c;        //P0_2,P0_3,P0_4,P0_5用作串口,第二功能 
    P2DIR &= ~0XC0;      //P0 优先作为UART0 ，优先级
 
    U0CSR |= 0x80;       //UART 方式 
    U0GCR |= 11;         //U0GCR与U0BAUD配合     
    U0BAUD |= 216;       // 波特率设为115200 
    UTX0IF = 0;          //UART0 TX 中断标志初始置位1  （收发时候）
    U0CSR |= 0X40;       //允许接收 
    IEN0 |= 0x84;        // 开总中断，接收中断    
}

void Uart_Send_String(char *Data,int len) 
{
 { 
  int j; 
  for(j=0;j<len;j++) 
  { 
    U0DBUF = *Data++; 
    while(UTX0IF == 0); //发送完成标志位
    UTX0IF = 0; 
  } 
 }
}

void main(void)
{
  InitLed();	//调用初始化函数 
  InitUart();
  while(1)
  {
    if(RXTXflag == 1)	//接收状态
    {

      if( temp != 0)
      {
        if((temp!='#')&&(datanumber<3)) 
          Rxdata[datanumber++] = temp;
        else
        {

          RXTXflag = 3;	//进入发送状态
        }

        temp = 0;
      }

    }
    if(RXTXflag == 3)	//检测接收到的数据
    {
      if(Rxdata[0]=='L')
        switch(Rxdata[1]-48)	//很重要，ASICC 码转成数字,判断 L 后面第一个数
        {
          case 1:	//如果是 L1
          {
            LED1=~LED1;	//低电平点亮 
            break;
          }
          case 2:	//如果是 L2
          {
            LED2=~LED2;
            break;
          }
        }

      RXTXflag = 1;
      datanumber = 0;	//指针归 0
    }
  }
}

#pragma vector = URX0_VECTOR 
  __interrupt void UART0_ISR(void) 
{ 
  URX0IF = 0;    // 清中断标志 
  temp = U0DBUF;                           
}
