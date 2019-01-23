#ifndef __DHT11_2_H
#define __DHT11_2_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO��������
#define DHT11_2_IO_IN()  {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=8<<20;}
#define DHT11_2_IO_OUT() {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=3<<20;}
////IO��������											   
#define	DHT11_2_DQ_OUT PBout(13) //���ݶ˿�	
#define	DHT11_2_DQ_IN  PBin(13)  //���ݶ˿�	

//IO��������
#define DHT11_3_IO_IN()  {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=11<<20;}
#define DHT11_3_IO_OUT() {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=8<<20;}
////IO��������											   
#define	DHT11_3_DQ_OUT PBout(8) //���ݶ˿�	
#define	DHT11_3_DQ_IN  PBin(8)  //���ݶ˿�	



u8 DHT11_2_Init(void);//��ʼ��DHT11
u8 DHT11_2_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_2_Read_Byte(void);//����һ���ֽ�
u8 DHT11_2_Read_Bit(void);//����һ��λ
u8 DHT11_2_Check(void);//����Ƿ����DHT11
void DHT11_2_Rst(void);//��λDHT11    
#endif















