#ifndef _DELAY_H_
#define _DELAY_H_
//8MHzÊ±ÖÓÏÂ

#include "STC12C5A60S2.H"

void delay_1ms(void);           //1msÑÓÊ±º¯Êý
void delay_nms(unsigned int n); //ÑÓÊ±nºÁÃë
void delay_nus(unsigned int n); //ÑÓÊ±NÎ¢Ãë,N>=5  ¾§Õñ:8MHz

#endif