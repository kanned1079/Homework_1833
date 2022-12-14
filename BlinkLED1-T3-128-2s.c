#include <ioCC2530.h>
#define LED1 P1_0
//#define LED2 P1_1
unsigned int count;
void InitT3()
{
  T3CTL |= 0x08 ; //开溢出中断
  T3IE = 1; //开总中断和 T3 中断
  T3CTL|=0XE0; //128 分频,128/16000000*N=0.5S,N=65200
  T3CTL &= ~0X03; //自动重装 00－>0xff65200/256=254(次)
  T3CTL |=0X10; //启动
  EA = 1; //开总中断
}

void InitLed(void)
{
  P1DIR |= 0x03;	
  LED1 = 1;	
  //LED2 = 0;
}

void main(void)
{
  InitLed(); //调用初始化函数
  InitT3();
  while(1){ }
}

#pragma vector = T3_VECTOR //定时器 T3
__interrupt void T3_ISR(void)
 {
    IRCON = 0x00; //清中断标志, 也可由硬件自动完成
    if(++count>254) //254 次中断后 LED 取反，闪烁一轮（约为 0.5 秒时间）
 {
  count = 0; // 计数清零
  LED1=~LED1;
  //LED2=~LED2;
}
 }
