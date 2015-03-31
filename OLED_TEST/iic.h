#ifndef _IIC_H_
#define _IIC_H_


#include "STC12C5A60S2.H"

#define DelayTime 10 //DelayTime���ڿ���IIC���ٶȣ���Щ�������ܲ���֧�ָ��ٵ�IICͨ��
             	     //���Ե���DelayTime������IIC���ٶ�

//�˿ڶ���
sbit SCL=P2^4; //IIC��ʱ����
sbit SDA=P2^3; //IIC��������
//��������
void IIC_Start();
void IIC_Stop();
void IIC_Ack();
void IIC_NAck();
unsigned char IIC_Get_Ack();
unsigned char IIC_Write_Byte(unsigned char dat);
unsigned char IIC_Read_Byte();

#endif