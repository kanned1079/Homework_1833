#include <ioCC2530.h>
#include "InitUART_Timer.h"	//ע���� option ������·��
#include "stdio.h"
/****************************************************************
�¶ȴ�������ʼ������
****************************************************************/ 
void initTempSensor(void)
 
{
  DISABLE_ALL_INTERRUPTS();		//�ر������ж� 
  InitClock();	//����ϵͳ��ʱ��Ϊ 32M
  TR0=0X01;	//set '1' to connectthe temperature sensorto the SOC_ADC.
  ATEST=0X01;	// Enablesthe temperature sensor

}
/****************************************************************
��ȡ�¶ȴ����� AD  ֵ����
****************************************************************/ 
float getTemperature(void)
{

  uint	value;
  ADCCON3	= (0x3E);	//ѡ�� 1.25V Ϊ�ο���ѹ��12 λ�ֱ��ʣ� ��Ƭ���¶ȴ���������
  ADCCON1 |= 0x30;	//ѡ�� ADC ������ģʽΪ�ֶ�
  ADCCON1 |= 0x40;	//���� AD ת��
  while(!(ADCCON1 & 0x80));	//�ȴ� AD  ת�����
  value =	ADCL >> 4;	//ADCL  �Ĵ����� 4  λ��Ч
  value |= (((UINT16)ADCH) << 4);
  return (value-1367.5)/4.5-4;	//���� AD  ֵ�������ʵ�ʵ��¶�,оƬ��
//�ֲ��д��¶�ϵ��Ӧ���� 4.5 /��
//�����¶�У���������ȥ 4�棨��ͬо Ƭ���ݾ������У����
}
/****************************************************************
������
****************************************************************/
void main(void)
{

  char I;
  char TempValue[6]; 
  float AvgTemp;
  InitUART0();	//��ʼ������
  initTempSensor();	//��ʼ�� ADC 
  while(1)
  {

    AvgTemp = 0;
    for(I = 0 ; I < 64 ; I++)
      {

        AvgTemp += getTemperature();
        AvgTemp=AvgTemp/2;	//ÿ���ۼӺ�� 2
      }
/****�¶�ת���� ascii �뷢��****/
    
    UartTX_Send_String("Wuchenghao",10);
    TempValue[0] = (unsigned char)(AvgTemp)/10 + 48;		//ʮλ 
    TempValue[1] = (unsigned char)(AvgTemp)%10 + 48;		//��λ 
    TempValue[2] = '.';	//С����
    TempValue[3] = (unsigned char)(AvgTemp*10)%10+48; //ʮ��λ 
    TempValue[4] = (unsigned char)(AvgTemp*100)%10+48; //�ٷ�λ 
    TempValue[5] = '\0';	//�ַ���������
    UartTX_Send_String( TempValue,6);
    Delayms(2000);	//ʹ�� 32M ���񣬹����� 2000 Լ���� 1S
  }
}
