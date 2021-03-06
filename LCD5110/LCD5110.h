/*******************************************************************************
 ************************* QQ858860583 *****************************************
 ************************* 正点原子论坛号：cornrn ******************************	
 *******************************************************************************/
#ifndef _LCD5110_H
#define _LCD5110_H
#include "stm32f10x_GPIO.h"

/******************************宽高像素 ******************************/
#define LCD_X_RES		84
#define LCD_Y_RES		48 
/**************************枚举 D/C模式选择 **************************/
typedef enum
{
  DC_CMD  = 0,	//写命令
	DC_DATA = 1		//写数据	
} DCType;
/**********************管脚配置 H: high, L: low***********************/
#define LCD_CTRL_PORT	GPIOA
#define LCD_RST			  GPIO_Pin_2
#define LCD_CE			  GPIO_Pin_3
#define LCD_DC			  GPIO_Pin_4

 
/***************************config as spi2 ***************************/

#define LCD_CLK			  GPIO_Pin_5
#define LCD_MOSI		  GPIO_Pin_7

#define LCD_RST_H()		GPIO_SetBits  (LCD_CTRL_PORT, LCD_RST)
#define LCD_RST_L()		GPIO_ResetBits(LCD_CTRL_PORT, LCD_RST)
#define LCD_CE_H()		GPIO_SetBits  (LCD_CTRL_PORT, LCD_CE)
#define LCD_CE_L()		GPIO_ResetBits(LCD_CTRL_PORT, LCD_CE)
#define LCD_DC_DATA()	GPIO_SetBits  (LCD_CTRL_PORT, LCD_DC)
#define LCD_DC_CMD()	GPIO_ResetBits(LCD_CTRL_PORT, LCD_DC)
#define LCD_MOSI_H()	GPIO_SetBits  (LCD_CTRL_PORT, LCD_MOSI)
#define LCD_MOSI_L()	GPIO_ResetBits(LCD_CTRL_PORT, LCD_MOSI)
#define LCD_CLK_H()		GPIO_SetBits  (LCD_CTRL_PORT, LCD_CLK)
#define LCD_CLK_L()		GPIO_ResetBits(LCD_CTRL_PORT, LCD_CLK)
 

/************************函数定义****************************/
//#define USESPI 1
void LCD5110_Init(void);
void LCD_Clear(void);
void LCD_SetXY(u8 X, u8 Y);
void LCD_SetContrast(u8 contrast);
void LCD_Send(u8 data, DCType dc);
void LCD_Write_Char(u8 ascii);
void LCD_Write_EnStr(u8 X, u8 Y, u8* s);
void LCD_Write_ChStr(u8 X, u8 Y);
void LCD_Write_Hanzi(u8 X, u8 Y,u8 GBK);
void LCD5110_IO_Configuration(void);
void SPI1_Config(void);
void DMA_SPI_Config(void);
void Array_chinese(void);
#define puts_xy(x,y,s) LCD_Write_EnStr(x, y, s)
#endif

