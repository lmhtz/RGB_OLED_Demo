#include "STC12C5A60S2.H"
#include "ssd1332.h"
#include "delay.h"
#include "img.h"
#include "pcf8563.h"
#include "myfun.h"
#include "uart.h"
#include "PWM_SOFT.H"
#include "KEY.h"


unsigned char	date_arry[11]={"2015:01:22"};
unsigned char	time_arry[9]={"12:00:00"};    
void main()
{
 timer0_init();
 OLED_init();
 time.year  =15; //向time中装入要设置的时间数据
 time.month = 1;
 time.day   =22;
 time.hour  =14;
 time.minute=25;
 time.second=50;
 time.week  = 4;
 P8563_Set_Time(); //设置时间，即将time中的时间数据写入PCF8563 
 UART_Init();  
 disp_all(0x00,0x00);    //black   

   
	while(1)
    {
			P8563_Read_Time(); //读取时间
			date_arry[2]=0x30+time.year/10;
			date_arry[3]=0x30+time.year%10;
			date_arry[5]=0x30+time.month/10;
			date_arry[6]=0x30+time.month%10;
			date_arry[8]=0x30+time.day/10;
			date_arry[9]=0x30+time.day%10;
			date_arry[10]=0;
			
			time_arry[0]=0x30+time.hour/10;
			time_arry[1]=0x30+time.hour%10;
			time_arry[3]=0x30+time.minute/10;
			time_arry[4]=0x30+time.minute%10;
			time_arry[6]=0x30+time.second/10;
			time_arry[7]=0x30+time.second%10;
			time_arry[8]=0;
 //disp_all(0x00,0x00);    //black  
			OLED_putstring(15,0,0x07,0xf8,date_arry); 
			OLED_putstring(15,8,0x00,0x1f,time_arry); 
			
			OLED_draw_rectangle(15,16,PWM_DUTY_B+15,23,255,0,0,255,0,0);
			delay_nms(10);
			OLED_draw_rectangle(PWM_DUTY_B+16,16,95,23,0,0,0,0,0,0);
			delay_nms(10);
			
			OLED_draw_rectangle(15,24,PWM_DUTY_G+15,31,0,255,0,0,255,0);
			delay_nms(10);
			OLED_draw_rectangle(PWM_DUTY_G+16,24,95,31,0,0,0,0,0,0);
			delay_nms(10);
			
			OLED_draw_rectangle(15,32,PWM_DUTY_R+15,39,0,0,255,0,0,255);
			delay_nms(10);
			OLED_draw_rectangle(PWM_DUTY_R+16,32,95,39,0,0,0,0,0,0);
			delay_nms(10);
			
			OLED_putstring(5,40,0x00,0x1f,"JION_IOT COLOR"); 
			OLED_draw_rectangle(15,48,78,55,PWM_DUTY_B<<2,PWM_DUTY_G<<2,PWM_DUTY_R<<2,PWM_DUTY_B<<2,PWM_DUTY_G<<2,PWM_DUTY_R<<2);
			OLED_putstring(5,56,0x00,0x1f,"Demo2015@fancy"); 
	if(0==KEY_R)	PWM_DUTY_R++;
	if(0==KEY_G)	PWM_DUTY_G++;
	if(0==KEY_B)	PWM_DUTY_B++;
	if(PWM_DUTY_R>63)	PWM_DUTY_R=0;
	if(PWM_DUTY_G>63)	PWM_DUTY_G=0;
	if(PWM_DUTY_B>63)	PWM_DUTY_B=0;
    }
        
}