#ifndef _IIC_H_
#define _IIC_H_


#include "STC12C5A60S2.H"

#define DelayTime 10 //DelayTime用于控制IIC的速度，有些器件可能并不支持高速的IIC通信
             	     //可以调整DelayTime来调节IIC的速度

//端口定义
sbit SCL=P2^4; //IIC的时钟线
sbit SDA=P2^3; //IIC的数据线
//函数声明
void IIC_Start();
void IIC_Stop();
void IIC_Ack();
void IIC_NAck();
unsigned char IIC_Get_Ack();
unsigned char IIC_Write_Byte(unsigned char dat);
unsigned char IIC_Read_Byte();

#endif