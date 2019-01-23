#include "sys.h"
#include "usart.h"
#include "usart2.h" 
#include "delay.h"
#include "led.h"
u8 uart2flag=0; 
u8 USART2_RX_BUF[USART2_REC_LEN];
/*
初始化串口 

*/
void usart2_init(u32 band)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	
	//重新定义管脚
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 引脚不能更改
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化   

  //Usart NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3 原3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3     原2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = band;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2
}
 /*发送一个字节数据*/
 void USART2SendByte(unsigned char SendData)
{	   
        USART_SendData(USART2,SendData);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart2_SendStringByLen(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart2_SendString(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART2, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
/*
串口2中断函数
*/
void USART2_IRQHandler(void)                	//串口2中断服务程序
	{
		 static u8 i;
 	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{	

		if(uart2flag==0)
		{
		     USART2_RX_BUF[0] = USART_ReceiveData(USART2);	
				if( USART2_RX_BUF[0]=='n') 
				 {
					 USART2SendByte('k'); //判断是否开始接收
					 uart2flag=1; i = 1;   //开始接收
				 }
				 else
				 {
					USART2_RX_BUF[0]=0;
				 }
		}
	else	
	  { 
				USART2_RX_BUF[i] = USART_ReceiveData(USART2);  //接收9位
				  i++; 
			if(i == 9) //接收完毕
			{
				  i=0;
					uart2flag=0;	 
			}
	  }	
}  
 }


