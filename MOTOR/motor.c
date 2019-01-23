#include "motor.h"
#include "stm32f10x.h"
#include "delay.h"
//引脚连接
//IN1：PB12
//IN2：PB13
//IN3：PB5
//IN4：PB8
//步进电机初始化函数
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_5|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	IN1 = 0;
	IN2 = 0;
	IN3 = 0;
	IN4 = 0;	
}
 
//步进电机正转函数
void Motorcw(int time)
{
  IN1 = 1;
	IN2 = 1;
	IN3 = 0;
	IN4 = 0;	
	delay_ms(time);
	
  IN1 = 0;
	IN2 = 1;
	IN3 = 1;
	IN4 = 0;	
	delay_ms(time);
	
	IN1 = 0;
	IN2 = 0;
	IN3 = 1;
	IN4 = 1;	
	delay_ms(time);
	
  IN1 = 1;
	IN2 = 0;
	IN3 = 0;
	IN4 = 1;	
	delay_ms(time);
	
}
//步进电机反转函数
void Motorse(int time)
{
  IN1 = 1;
	IN2 = 0;
	IN3 = 0;
	IN4 = 1;	
	delay_ms(time);

		IN1 = 0;
	IN2 = 0;
	IN3 = 1;
	IN4 = 1;	
	delay_ms(time);
	
	  IN1 = 0;
	IN2 = 1;
	IN3 = 1;
	IN4 = 0;	
	delay_ms(time);
	
	  IN1 = 1;
	IN2 = 1;
	IN3 = 0;
	IN4 = 0;	
	delay_ms(time);

}
//由于   *一个脉冲*   *输出轴*  转0.08789度（电机实转0.08789*64=5.625度），即步进角为5.625度。则转完A-B-C-D为  *8个脉冲*  ，即0.08789*8=0.70312度。
//若称A-B-C-D为一个周期，则j为需要的转完angle角度所需的周期数。
void Motorcw_angle(int angle,int speed) //正转
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorcw(speed);
	}
	MotorStop();
}
void Motorse_angle(int angle,int speed) //反转
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorse(speed);
	}
	MotorStop();
}
void MotorStop(void)  
{  
 	IN1 = 0;
	IN2 = 0;
	IN3 = 0;
	IN4 = 0;	
}