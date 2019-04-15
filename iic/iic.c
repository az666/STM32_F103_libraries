/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * 文件名  ：iic.h
 * 描述    ：iic驱动文件编写。本文件是我在学习iic后自己编写，部分思路参考的原子的iic代码       
 * 实验平台：原子开发板mini版
 * 库版本  ：ST3.5.0
 * 日期    ：2017
 * 作者    ：沈慧想
**********************************************************************************/
#include "iic.h"

/*********************************************************************************/
/*
函数名：iic_init
功  能：配置SDA 和SCL端口
参  数：无
返回值：无
*/
void iic_init(void)
{
	/*****配置GPIO口**************************************/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOIIC, ENABLE);
   
	GPIO_InitStructure.GPIO_Pin=IIC_SCL_Pin|IIC_SDA_Pin;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIO_IIC, &GPIO_InitStructure);	
	
	/********将IIC的 SCL SDA 上拉释放总线******************/
	SDA_PIN_OUT=1;
	SCL_PIN_OUT=1;
}
/*
函数名：iic_start
功  能：启动iic，启动方式，在SCL高电平期间将SDA由高置低
参  数：无
返回值：无
*/
void iic_start(void)
{
	IIC_SDA_OUT();
	SDA_PIN_OUT=1;
	SCL_PIN_OUT=1;
	delay_us(1);
	SDA_PIN_OUT=0;
	delay_us(1);
	SCL_PIN_OUT=0;
}
/*
函数名：iic_stop
功  能：停止传输数据，实现方式在SCL高电平期间将SDA由低置高
参  数：无
返回值：无
*/
void iic_stop(void)
{
	
    SCL_PIN_OUT=0;
	IIC_SDA_OUT();	
	SDA_PIN_OUT=0;
	delay_us(1);
	SCL_PIN_OUT=1;
	SDA_PIN_OUT=1;
	delay_us(1);
}
/*
函数名：iic_ack
功  能：接收从机应答信号，释放掉总线读取SDA置看是否有负脉冲,
        当一段时间无应答默认接收完毕
参  数：无
返回值：无
*/
u8 iic_wait_ack(void)
{
	u8 i=0;
	IIC_SDA_IN();
    SDA_PIN_OUT=1;delay_us(1);
	SCL_PIN_OUT=1;delay_us(1);
	while(SDA_PIN_IN)
	{
		i++;
		if(i>250) 
		{		
            iic_stop();			//如果i>255则产生非应答信号，iic停止
			return 1;
		}
		
	}
	SCL_PIN_OUT=0;//时钟输出0 
	return 0;
}
/*
函数名：iic_nask
功  能：产生非应答信号
参  数：无
返  回：无
*/
void iic_nack(void)
{
	SCL_PIN_OUT=0;
	IIC_SDA_OUT();
	SDA_PIN_OUT=1;
	delay_us(1);
	SCL_PIN_OUT=1;
	delay_us(1);
	SCL_PIN_OUT=0;
}	
/*
函数名：iic_ask
功  能：产生ask应答
参  数：无
返  回：无
*/
void iic_ack(void)
{
	SCL_PIN_OUT=0;
	IIC_SDA_OUT();
	SDA_PIN_OUT=0;
	delay_us(1);
	SCL_PIN_OUT=1;
	delay_us(1);
	SCL_PIN_OUT=0;
}
/*
函数名：iic_bit_write
功  能：传送一个字节
参  数：u8
返回值：无
*/
void iic_byte_write(u8 buf)
{
    u8 i;
	IIC_SDA_OUT();
	SCL_PIN_OUT=0;
	for(i=1;i<=8;i++)
	{
		SDA_PIN_OUT=(buf>>(8-i))&0x01;
		delay_us(1);
		SCL_PIN_OUT=1;
		delay_us(1);
		SCL_PIN_OUT=0;
		delay_us(1);		
	}
}
/*
函数名：iic_bit_read
功  能：主机读取一个字节
参  数：ask
返回值：
*/
u8 iic_byte_read(unsigned char ask)
{
	unsigned char  i,buf=0;
	IIC_SDA_IN();
	for(i=0;i<8;i++)
	{
	   SCL_PIN_OUT=0;
	   delay_us(1);
	   SCL_PIN_OUT=1;
	   buf <<=1;
	   if(SDA_PIN_IN)
		   buf++;
	    delay_us(1);
	}
	if(!ask)
		iic_nack();
	else
		iic_ack();
	return buf;
}
