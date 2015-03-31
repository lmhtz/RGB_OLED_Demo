#include	"STC12C5A60S2.H"
#include	"PWM_SOFT.H"

//ռ�ձȺ�PWM������
unsigned char	PWM_DUTY_COUNT	=	0;
unsigned char	PWM_DUTY_R		=	0;
unsigned char	PWM_DUTY_G		=	0;
unsigned char	PWM_DUTY_B		=	0;


/**********************************************/
void timer0_init(void)
{
    
    TMOD |=  0x02;    // Timer0 set as 8bit reload Timer
    TH0 = Timer0_Reload;  //Timer0 Load
    TL0 = Timer0_Reload;
    ET0 = 1;        //Timer0 Interrupt Enable
    TR0 = 1;        //Timer0 Run
    EA = 1;         //�����ж�
		PWM_R	= PWM_OFF; 
		PWM_G	= PWM_OFF;
		PWM_B	= PWM_OFF;
	
} 


/********************** Timer0�жϺ��� ************************/
void timer0_isr (void) interrupt 1
{

        
    if(++PWM_DUTY_COUNT == 64)      //PWM���ڽ��������¿�ʼ�µ�����
    {
      PWM_DUTY_COUNT = 0;

		if(PWM_DUTY_R)       PWM_R	= PWM_ON;
    if(PWM_DUTY_G)       PWM_G	= PWM_ON;
    if(PWM_DUTY_B)       PWM_B	= PWM_ON;
    }
    if(PWM_DUTY_COUNT >	PWM_DUTY_R)       PWM_R	= PWM_OFF;  //�ж�PWMռ�ձ��Ƿ����
    if(PWM_DUTY_COUNT >	PWM_DUTY_G)       PWM_G	= PWM_OFF;
    if(PWM_DUTY_COUNT >	PWM_DUTY_B)       PWM_B	= PWM_OFF;

}
