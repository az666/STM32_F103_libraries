/******************** (C) COPYRIGHT 2017 shen hui xiang **************************
 * �ļ���  ��iic.h
 * ����    ��iic�����ļ���д����������ԭ�ӵ�iic�����ļ������ļ�������ѧϰiic���Լ���д������˼·�ο���ԭ�ӵ�iic����       
 * ʵ��ƽ̨��ԭ�ӿ�����mini��
 * ��汾  ��ST3.5.0
 * ����    ��2017
 * ����    �������
**********************************************************************************/
#ifndef __IIC__H_
#define __IIC__H_
#include "delay.h"

#define IIC_SCL_Pin  GPIO_Pin_14
#define IIC_SDA_Pin  GPIO_Pin_15
#define GPIO_IIC     GPIOC
#define RCC_APB2Periph_GPIOIIC RCC_APB2Periph_GPIOC

#define IIC_SDA_OUT()  {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=0x30000000;}//����ģʽ������������ģʽ
#define IIC_SDA_IN()   {GPIOC->CRH&=0X0FFFFFFF;GPIOC->CRH|=0x80000000;}//ͨ���������50MZ

#define SDA_PIN_OUT       PCout(15)
#define SCL_PIN_OUT       PCout(14)
#define SDA_PIN_IN        PCin(15)

void iic_init(void);
void iic_start(void);
void iic_stop(void);
u8 iic_wait_ack(void);
void iic_byte_write(u8 buf);
u8 iic_byte_read(unsigned char ask);
void iic_page_write(u8 device_address,u8 word_address,u8 byte_num,u8 *send_buff);
void iic_nbyte_read(u8 device_address,u8 word_address,u8 byte_num ,u8 *receive_buff);

void AT24_onebyte_write(u8 device_address,u8 word_address,u8 send_buff);
u8  AT24_onebyte_read(u8 device_address,u8 word_address);
void AT24_nbyte_read(u8 device_address,u8 word_address,u8 num,u8 *receive_buf);
#endif
