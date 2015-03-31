#ifndef	_PWM_SOFT_H_
#define	_PWM_SOFT_H_


//************** PWM8 �����ͳ����Լ�IO�ڶ��� ***************
//6λ�ֱ�����ռ�ձ����ֵ63������������
#define     PWM_ON          1   // ����ռ�ձȵĵ�ƽ, 1 �� 0
#define     PWM_OFF         (!PWM_ON)  
#define		PWM_BIT			6	//6λ�ֱ���

#define MAIN_FOSC       11059200UL  //������ʱ��
#define	PWM_FOSC		100			//PWM���Ƶ��
#define	Timer0_Rate		(PWM_FOSC*64)//6λ�ֱ���ʱ�ж�Ƶ��
#define Timer0_Reload   (256 - MAIN_FOSC / 12 / Timer0_Rate)        //Timer 0 ��װֵ

//����pwm����˿�
sbit	PWM_R	=	P1^3;
sbit	PWM_G	=	P1^2;
sbit	PWM_B	=	P1^4;


extern	unsigned char	PWM_DUTY_R;
extern	unsigned char	PWM_DUTY_G;
extern	unsigned char	PWM_DUTY_B;

extern	void timer0_init(void);
extern	void timer0_isr (void);

#endif
