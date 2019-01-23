#ifndef __DHT11_2_H
#define __DHT11_2_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO方向设置
#define DHT11_2_IO_IN()  {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=8<<20;}
#define DHT11_2_IO_OUT() {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=3<<20;}
////IO操作函数											   
#define	DHT11_2_DQ_OUT PBout(13) //数据端口	
#define	DHT11_2_DQ_IN  PBin(13)  //数据端口	

//IO方向设置
#define DHT11_3_IO_IN()  {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=11<<20;}
#define DHT11_3_IO_OUT() {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=8<<20;}
////IO操作函数											   
#define	DHT11_3_DQ_OUT PBout(8) //数据端口	
#define	DHT11_3_DQ_IN  PBin(8)  //数据端口	



u8 DHT11_2_Init(void);//初始化DHT11
u8 DHT11_2_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_2_Read_Byte(void);//读出一个字节
u8 DHT11_2_Read_Bit(void);//读出一个位
u8 DHT11_2_Check(void);//检测是否存在DHT11
void DHT11_2_Rst(void);//复位DHT11    
#endif















