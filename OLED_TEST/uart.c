#include "STC12C5A60S2.H"
#include <string.h>
#include "uart.h"
#include "myfun.h"

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڳ�ʼ��
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������
 - ����˵������
 **************************************************************************/

void UART_Init()     
{
 PCON|=0x80; //PCON�����λSMOD=1ʱ�����ʼӱ� 
 TMOD|=0x20;  //ʱ��1Ϊ��ʽ2 ��ֵ�Զ�װ�� ����������
 TH1 = TL1 =  256-(FOSC*2/12/32/BAUD);
 SCON|=0x50;	 //��������Ϊ��ʽ1,REN=1,��������
 TR1=1;      //������ʱ��1
 //ES=1;       //ʹ�ܴ��ڽ����жϣ�
 //EA=1;       //�������ж�
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ����жϴ�������
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��(�ڴ��жϺ����г����������Ӵ����յ�������)
 - ����˵������
 - ����˵������
 **************************************************************************/

void sio_int() interrupt 4  //�����жϺ���
{
 ES=0;
  //�����жϴ���

 ES=1;
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ����ֽڵĺ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����mydata:Ҫ���͵�һ���ֽ�
 - ����˵������
 - ע������һ���ֽڣ��Ǵ��ڷ��͵Ļ�������
 **************************************************************************/

void UART_Send_Byte(unsigned char mydata)	
{
 TI=0;
 SBUF=mydata;
 while(!TI);
 TI=0;
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ���0d 0a �����س�����
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������
 - ����˵������
 - ע���˺������Ƿ���0d 0a�������ֽڣ��ڡ������նˡ��ϻ��лس����е�Ч��
 **************************************************************************/

void UART_Send_Enter()
{
 UART_Send_Byte(0x0d);
 UART_Send_Byte(0x0a);
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ����ַ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����s:ָ���ַ�����ָ��
 - ����˵������
 - ע��������ַ�������'\n'����ᷢ��һ���س�����
 **************************************************************************/

void UART_Send_Str(char *s)
{
 int len=strlen(s)-1;
 int i;
 for(i=0;i<len;i++)
 UART_Send_Byte(s[i]);
 if(s[i]=='\n') 
 {
  UART_Send_Enter();
 }
 else
 {
  UART_Send_Byte(s[i]);
 }
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ�����ֵ
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����dat:Ҫ���͵���ֵ
 - ����˵������
 - ע�������лὫ��ֵתΪ��Ӧ���ַ��������ͳ�ȥ������ 4567 תΪ "4567" 
 **************************************************************************/

void UART_Put_Num(unsigned long dat)
{
 char temp[20];
 u32tostr(dat,temp);
 UART_Send_Str(temp);
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ��͵�����Ϣ
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����inf:ָ����ʾ��Ϣ�ַ�����ָ��
             dat:һ����ֵ��ǰ�����ʾ��Ϣ������˵�������ֵ������
 - ����˵������
 **************************************************************************/

void UART_Put_Inf(char *inf,unsigned long dat)
{
 UART_Send_Str(inf);
 UART_Put_Num(dat);
 UART_Send_Str("\n");  
}