#include "delay.h"
#include "intrins.h"

void delay_1ms(void)//1ms��ʱ����@11.0592MHz
{
	unsigned char i, j;

	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


void delay_nms(unsigned int n)//��ʱn����
{
    unsigned int i;
    
    for(i=0;i<n;i++)//ִ��n��1������ʱ
    {
        delay_1ms(); 
    }
}

void delay_nus(unsigned int n)//��ʱN΢��,N>=5  ����:11.0592MHz
{
    unsigned int i;
    
    for(i=5;i<n;i++)
    {
      _nop_();
      _nop_();
    } 
}
