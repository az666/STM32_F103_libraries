#ifndef __MOTOR_H
#define __MOTOR_H
#define IN1  PBout(12)	
#define IN2  PBout(13)	
#define IN3  PBout(5)
#define IN4  PBout(8)
void Motor_Init(void); //初始化IO
void MotorStop(void) ; //停止转动
void Motorcw_angle(int angle,int speed); //正转固定角度
void Motorse_angle(int angle,int speed); //反转
void Motorcw(int time);//正转
void Motorse(int time);//反转
#endif