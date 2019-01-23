#include "sys.h"
#include "usart.h"
#include "usart2.h" 
#include "delay.h"
#include "led.h"
u8 uart2flag=0; 
u8 USART2_RX_BUF[USART2_REC_LEN];
/*
��ʼ������ 

*/
void usart2_init(u32 band)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	
	//���¶���ܽ�
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // ���Ų��ܸ���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��   

  //Usart NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3 ԭ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3     ԭ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = band;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2
}
 /*����һ���ֽ�����*/
 void USART2SendByte(unsigned char SendData)
{	   
        USART_SendData(USART2,SendData);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
} 

/*
���ݳ����򴮿�2 ��������
*/
void usart2_SendStringByLen(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2, data[i]);         //�򴮿�2��������
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		//i++;
	}
	//i++;
}
/*����3 �������ݵ���λ�� data ��\0��β*/
void usart2_SendString(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART2, data[i]);         //�򴮿�2��������
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		i++;
	}
	i++;
}
/*
����2�жϺ���
*/
void USART2_IRQHandler(void)                	//����2�жϷ������
	{
		 static u8 i;
 	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{	

		if(uart2flag==0)
		{
		     USART2_RX_BUF[0] = USART_ReceiveData(USART2);	
				if( USART2_RX_BUF[0]=='n') 
				 {
					 USART2SendByte('k'); //�ж��Ƿ�ʼ����
					 uart2flag=1; i = 1;   //��ʼ����
				 }
				 else
				 {
					USART2_RX_BUF[0]=0;
				 }
		}
	else	
	  { 
				USART2_RX_BUF[i] = USART_ReceiveData(USART2);  //����9λ
				  i++; 
			if(i == 9) //�������
			{
				  i=0;
					uart2flag=0;	 
			}
	  }	
}  
 }


