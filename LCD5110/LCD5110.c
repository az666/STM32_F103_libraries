
/*******************************************************************************
 ************************* QQ858860583 *****************************************
 ************************* 正点原子论坛号：cornrn ******************************	
 *******************************************************************************/

#include "LCD5110.h"
#include "Pixel_EN.h"
#include "delay.h"
#include "string.h" 
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
//#include "Pixel_CH.h"
static u8 lcd_buf[84*6] ;
DMA_InitTypeDef DMA_initstructure ;
/*******************************************************************************
* Function Name  : LCD_Init
* Description    : LCD初始化
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD5110_Init(void)
{
	  LCD5110_IO_Configuration();
	  //复位LCD_低电平脉冲
	  LCD_RST_L();		
	  delay_ms(5);
   	LCD_RST_H();
	  //复位串行接口_高电平脉冲
	  LCD_CE_H(); 
	  delay_ms(5);
	  LCD_CE_L(); 
	  //设置LCD
    LCD_Send(0x21, DC_CMD);	//使用扩展命令设置LCD模式
    LCD_Send(0xC8, DC_CMD);	//设置偏置电压
    LCD_Send(0x06, DC_CMD);	//温度校正
    LCD_Send(0x13, DC_CMD); //1:48
    LCD_Send(0x20, DC_CMD);	//使用基本命令
    LCD_Send(0x0C, DC_CMD);	//设定显示模式，反转显示
}
/*******************************************************************************
* Function Name  : LCD_SetContrast
* Description    : 设置LCD对比度(对比度范围: 0~127)
* Input          : u8 contrast
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetContrast(u8 contrast)
{
    LCD_Send(0x21, DC_CMD);
    LCD_Send(0x80 | contrast, DC_CMD);
    LCD_Send(0x20, DC_CMD);
}
/*******************************************************************************
* Function Name  : LCD_SetXY
* Description    : 设置LCD当前坐标
* Input          : u8 X, u8 Y	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetXY(u8 X, u8 Y)
{
	if (X>13) X = 13;
	if (Y>5) Y = 5;
	X *= 6;
	//Y *= 8;
	LCD_Send(0x80 | X, DC_CMD);    // 列 
	delay_ms(10)         ;  
	LCD_Send(0x40 | Y, DC_CMD);    // 行
}
/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : LCD清屏
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(void)
{
	u16 i;
  LCD_Send(0x80, DC_CMD);
	delay_ms(5);
	LCD_Send(0x40, DC_CMD);
	for(i=0; i<504; i++)
	LCD_Send(0, DC_DATA);	  
}
/*******************************************************************************
* Function Name  : LCD_Send
* Description    : 向LCD发送数据
* Input          : u8 data, DCType dc
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Send(u8 data, DCType dc)
{
	u8 i=8;
	#if USESPI
  while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE ) == RESET );
	if (dc==DC_CMD)
		LCD_DC_CMD();	//发送命令
	else
		LCD_DC_DATA();//发送数据
    SPI_I2S_SendData(SPI1, data);
    //等待数据完成，否者 LCD_SET_XY 会有问题
    while( SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE ) == RESET );
	#else
   	if (dc==DC_CMD)
		LCD_DC_CMD();	//发送命令
	else
		LCD_DC_DATA();//发送数据
	while (i--)
	{
		LCD_CLK_L();
		if(data&0x80)
			LCD_MOSI_H();	/* MSB first */
		else 
			LCD_MOSI_L();
		LCD_CLK_H();
		data <<= 1;		/* Data shift */
	}
	#endif
}
/*******************************************************************************
* Function Name  : LCD_Write_Char
* Description    : 向LCD写一个英文字符
* Input          : u8 ascii
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Write_Char(u8 ascii)
{
    u8 n;
    ascii -= 32; //ASCII码-32
    for (n=0; n<6; n++)
		LCD_Send(Font6x8[ascii][n], DC_DATA);
}
/*******************************************************************************
* Function Name  : LCD_Write_Char
* Description    : 向LCD写一个汉字
* Input          : u8 ascii
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Write_Hanzi(u8 X, u8 Y,u8 GBK)
{
    u8 n;
     LCD_SetXY(X,Y); 
     for (n=0; n<12; n++)
	      {      
		           LCD_Send(Font12x16_chinese[GBK][n], DC_DATA);
		    }
	 
	  delay_ms(10);
		LCD_SetXY(X,Y+1); 
    for (n=12; n<24; n++)
	    {      
		         LCD_Send(Font12x16_chinese[GBK][n], DC_DATA);
		  }
			
}
/*******************************************************************************
* Function Name  : LCD_Write_EnStr
* Description    : 向LCD写英文字符串
* Input          : u8 ascii
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Write_EnStr(u8 X, u8 Y, u8* s)
{
    u8 * str = s;
    int i = 0;
    int lcd_index =0;
    if(str == 0 )
    {
        return ;
    }
    //等待上次DMA请求结束
    while(DMA_GetCurrDataCounter(DMA1_Channel3)) ;  
    LCD_SetXY(X,Y);
    while(*str)
    {
        //拷贝显示数据到缓冲区
        for(i=0;i<6;i++)
        {
            lcd_buf[lcd_index ++ ] = Font6x8[*str - 32][i];
        }
					//memcpy(lcd_buf+6*str,&Font6x8[*str - 32][0],6);	
        str ++ ;
    }
    lcd_buf[lcd_index ++ ] = 0 ; // lcd_index ++ 多发送一个0否者最后一个字符会缺少一个像素
    #if USESPI
			DMA_initstructure.DMA_BufferSize = lcd_index ;
		 
			DMA_Cmd(DMA1_Channel3, DISABLE); 
			DMA_Init( DMA1_Channel3, &DMA_initstructure) ;
			DMA_Cmd(DMA1_Channel3, ENABLE);
			LCD_DC_DATA();  
			SPI_I2S_DMACmd( SPI1, SPI_I2S_DMAReq_Tx, ENABLE) ;
    #else
    for(i = 0 ;i<lcd_index ;i++)
    {
        LCD_Send(lcd_buf[i], DC_DATA);
    }
    #endif
}
/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD5110_IO_Configuration(void)
{  	 
	GPIO_InitTypeDef GPIO_InitStructure;
	/*LCD5110_LCD_CTRL_PORT*/
 	GPIO_InitStructure.GPIO_Pin =LCD_RST|LCD_CE|LCD_DC|LCD_CLK|LCD_MOSI	;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_Init(LCD_CTRL_PORT, &GPIO_InitStructure);
  /*config spi1 ,clk mosi */
#if USESPI
 	GPIO_InitStructure.GPIO_Pin = LCD_CLK|LCD_MOSI;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif
}

/*******************************************************************************
* Function Name  : DMA_SPI_Config
* Description    : DMA初始化
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_SPI_Config(void)
{  
   // 初始化DMA 结构体
    DMA_initstructure.DMA_BufferSize = 0 ;
    DMA_initstructure.DMA_DIR = DMA_DIR_PeripheralDST ;
    DMA_initstructure.DMA_M2M = DISABLE ;
    DMA_initstructure.DMA_MemoryBaseAddr = (u32)lcd_buf;
    DMA_initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte ;
    DMA_initstructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
    DMA_initstructure.DMA_Mode = DMA_Mode_Normal;
    //SPI1 data rigester address 
    DMA_initstructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR ;
    DMA_initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ;
    DMA_initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_initstructure.DMA_Priority = DMA_Priority_High ;  
}
/*******************************************************************************
* Function Name  : SPI1_Config
* Description    : SPI1初始化
* Input          : None	
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16 ;// SPI_速度~
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge ;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CRCPolynomial = 0x07;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB ;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master ;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
    SPI_I2S_SendData(SPI1, 00); 
}

