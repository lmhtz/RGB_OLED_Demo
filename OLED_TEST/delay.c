#include "delay.h"
#include "intrins.h"

void delay_1ms(void)//1ms—” ±∫Ø ˝@11.0592MHz
{
	unsigned char i, j;

	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


void delay_nms(unsigned int n)//—” ±n∫¡√Î
{
    unsigned int i;
    
    for(i=0;i<n;i++)//÷¥––n¥Œ1∫¡√Î—” ±
    {
        delay_1ms(); 
    }
}

void delay_nus(unsigned int n)//—” ±NŒ¢√Î,N>=5  æß’Ò:11.0592MHz
{
    unsigned int i;
    
    for(i=5;i<n;i++)
    {
      _nop_();
      _nop_();
    } 
}
