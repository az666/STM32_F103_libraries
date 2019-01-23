#include "motor.h"
#include "stm32f10x.h"
#include "delay.h"
//��������
//IN1��PB12
//IN2��PB13
//IN3��PB5
//IN4��PB8
//���������ʼ������
void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_5|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	IN1 = 0;
	IN2 = 0;
	IN3 = 0;
	IN4 = 0;	
}
 
//���������ת����
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
//���������ת����
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
//����   *һ������*   *�����*  ת0.08789�ȣ����ʵת0.08789*64=5.625�ȣ�����������Ϊ5.625�ȡ���ת��A-B-C-DΪ  *8������*  ����0.08789*8=0.70312�ȡ�
//����A-B-C-DΪһ�����ڣ���jΪ��Ҫ��ת��angle�Ƕ��������������
void Motorcw_angle(int angle,int speed) //��ת
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorcw(speed);
	}
	MotorStop();
}
void Motorse_angle(int angle,int speed) //��ת
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