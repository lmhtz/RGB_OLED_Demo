#ifndef _PCF8563_H_
#define _PCF8563_H_


typedef	struct   //ʱ��ṹ�壬��������,�֣�ʱ���գ��ܣ��£���
{
 unsigned char second;
 unsigned char minute;
 unsigned char hour;
 unsigned char day;
 unsigned char week;
 unsigned char month;
 unsigned char year;
}T_Time;

typedef	struct  //����ʱ������ݣ���������ֵ������ʱ��ֵ 
{
 unsigned char set_value;
 unsigned char dcounter_value;
}T_DownCounter;

extern T_Time time; //����װʱ�����ݣ���Ҫ���ⲿ����
extern T_DownCounter dcounter;

//��������
unsigned char P8563_Read_Time();
unsigned char P8563_Set_Time();
unsigned char P8563_Read_DownCounter();
unsigned char P8563_Set_DownCounter();

#endif