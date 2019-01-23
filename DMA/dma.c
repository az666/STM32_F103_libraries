#include "dma.h"

#define  DMASIZE 1024
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//DMA ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
u8 sendbuf[1024];
u8 receivebuf[1024];
static void _uart2_dma_configuration()
{
  DMA_InitTypeDef DMA_InitStructure;
 
  /* DMA1 Channel6 (triggered by USART1 Rx event) Config */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,
                        ENABLE);
 
  /* DMA1 Channel5 (triggered by USART1 Rx event) Config */
  DMA_DeInit(DMA1_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;// ��ʼ�������ַ���൱�ڡ��ļҿ�ݡ�  
  DMA_InitStructure.DMA_MemoryBaseAddr =(u32)receivebuf;// �ڴ��ַ���൱�ڼ��Ź�
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//������Ϊ������Դ����Ϊ�տ��
  DMA_InitStructure.DMA_BufferSize = DMASIZE ;// ���������������Ӵ�С
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // �����ַ�������������Ӷ�Ӧ�Ŀ�ݲ���
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// �ڴ����
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //�����ֽڿ�ȣ��������������С�������������㣬���ǰ�����㣩 
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// �ڴ��ֽڿ�ȣ���������װ��ݵĶ���(�����������ǰ����ʽ��з�װ)
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ����ģʽ�������˾Ͳ��ڽ����ˣ�������ѭ���洢
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;// ���ȼ��ܸߣ���Ӧ��ݾ��ǼӼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // �ڴ�������ͨ�ţ������ڴ浽�ڴ� 
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);// �Ѳ�����ʼ������������ݹ�˾��Э��
 
  DMA_Cmd(DMA1_Channel5, ENABLE);// ����DMA�������ݹ�˾ǩ����ͬ����ʽ��Ч
 
  /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART2->DR;  // �����ַ������1�� �������Ŀ��
  DMA_InitStructure.DMA_MemoryBaseAddr =(u32)sendbuf;// �����ڴ��ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;// ����Ϊ��������Ŀ�ĵأ����������ݣ�������Ƿ���
  DMA_InitStructure.DMA_BufferSize = 0;  //���ͳ���Ϊ0����δ�п����Ҫ����
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);//��ʼ��
 
  USART_ITConfig(USART2, USART_IT_TC, ENABLE);// ʹ�ܴ��ڷ�������ж�
  USART_DMACmd(USART2, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);// ʹ��DMA���ڷ��ͺͽ�������
}
   

 

























