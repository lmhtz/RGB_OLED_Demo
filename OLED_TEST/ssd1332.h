//目标芯片 : M16 
//作者：陈超
//版本：第二版
//时钟: 8.0000Mhz 
#ifndef _SSD1332_H_
#define _SSD1332_H_

#include "STC12C5A60S2.H"
#include "typedef.h"

#define OLED_RECTANGLE_FILL_ENABLE()    WriteCommand(0x26),WriteCommand(0x01)
#define OLED_RECTANGLE_FILL_DISABLE()   WriteCommand(0x26),WriteCommand(0x00)


//D0->SCLK	D1->SDIN,硬件SPI驱动 sclk-P17sdin-P15
sbit	OLED_DC=P2^0;
sbit	OLED_CS=P4^0;
//sbit	OLED_SCLK=P2^2;
//sbit	OLED_SDIN=P2^3;
sbit	OLED_RST=P2^1;

//以上为接口定义

void SPI_Init(void);
extern void disp_all(unsigned char data1,unsigned char data2);
extern unsigned char ReadData(void);
extern unsigned char ReadCommand(void);
extern void WriteCommand(unsigned char com);
extern void WriteData(unsigned char dat);
extern void OLED_init(void);
extern void OLED_dot(uchar x,uchar y,uchar R,uchar G,uchar B);
extern void OLED_circle(uchar X,uchar Y,uchar R,uchar R1,uchar G1,uchar B1); 
extern void OLED_draw_rectangle(uchar x1,uchar y1,uchar x2,uchar y2,uchar R1,uchar G1,uchar B1,uchar R2,uchar G2,uchar B2);
extern void OLED_draw_line(uchar x1,uchar y1,uchar x2,uchar y2,uchar R,uchar G,uchar B);
extern void OLED_draw_img(uchar x,uchar y,uchar x_size,uchar y_size,uchar image[]);
extern void OLED_putstring(uchar x,uchar y,uchar colorH,uchar colorL,uchar *text);
extern void OLED_write_chinese(uchar x,uchar y,uchar num,uchar buff[][32]);

#endif
