#ifndef __OLED_H
#define __OLED_H	 
#include "sys.h"


#define SDA  PBout(6)	// PB10	
#define SCL  PBout(7)	// PB11
void LED_Init(void);//≥ı ºªØ
void OLED_Fill(unsigned char bmp_dat);
void OLED_IOInit(void);
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_WrDat(unsigned char IIC_Data);
void OLED_WrCmd(unsigned char IIC_Command);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_Init(void);
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[]);
void LCD_8x16Ch(unsigned char x,unsigned char y,unsigned char N);
void LCD_P24x48Ch(unsigned char x, unsigned char y, unsigned char N);
void LCD_P16x16Ch(unsigned char x,unsigned char y,unsigned char N);	 
#endif