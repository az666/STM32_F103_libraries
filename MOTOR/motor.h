#ifndef __MOTOR_H
#define __MOTOR_H
#define IN1  PBout(12)	
#define IN2  PBout(13)	
#define IN3  PBout(5)
#define IN4  PBout(8)
void Motor_Init(void); //��ʼ��IO
void MotorStop(void) ; //ֹͣת��
void Motorcw_angle(int angle,int speed); //��ת�̶��Ƕ�
void Motorse_angle(int angle,int speed); //��ת
void Motorcw(int time);//��ת
void Motorse(int time);//��ת
#endif