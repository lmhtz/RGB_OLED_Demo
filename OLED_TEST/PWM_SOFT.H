#ifndef	_PWM_SOFT_H_
#define	_PWM_SOFT_H_


//************** PWM8 变量和常量以及IO口定义 ***************
//6位分辨率是占空比最大值63！！！！！！
#define     PWM_ON          1   // 定义占空比的电平, 1 或 0
#define     PWM_OFF         (!PWM_ON)  
#define		PWM_BIT			6	//6位分辨率

#define MAIN_FOSC       11059200UL  //定义主时钟
#define	PWM_FOSC		100			//PWM输出频率
#define	Timer0_Rate		(PWM_FOSC*64)//6位分辨率时中断频率
#define Timer0_Reload   (256 - MAIN_FOSC / 12 / Timer0_Rate)        //Timer 0 重装值

//定义pwm输出端口
sbit	PWM_R	=	P1^3;
sbit	PWM_G	=	P1^2;
sbit	PWM_B	=	P1^4;


extern	unsigned char	PWM_DUTY_R;
extern	unsigned char	PWM_DUTY_G;
extern	unsigned char	PWM_DUTY_B;

extern	void timer0_init(void);
extern	void timer0_isr (void);

#endif

