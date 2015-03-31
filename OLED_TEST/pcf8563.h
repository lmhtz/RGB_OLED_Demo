#ifndef _PCF8563_H_
#define _PCF8563_H_


typedef	struct   //时间结构体，包括了秒,分，时，日，周，月，年
{
 unsigned char second;
 unsigned char minute;
 unsigned char hour;
 unsigned char day;
 unsigned char week;
 unsigned char month;
 unsigned char year;
}T_Time;

typedef	struct  //倒计时相关数据，包括设置值，倒计时数值 
{
 unsigned char set_value;
 unsigned char dcounter_value;
}T_DownCounter;

extern T_Time time; //用来装时间数据，需要在外部定义
extern T_DownCounter dcounter;

//函数声明
unsigned char P8563_Read_Time();
unsigned char P8563_Set_Time();
unsigned char P8563_Read_DownCounter();
unsigned char P8563_Set_DownCounter();

#endif