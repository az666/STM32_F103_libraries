#ifndef __GY30__H_
#define __GY30__H_
#include "iic.h"
#include "delay.h"
/*************************************************************/

#define GYAddressWrite 0x46
#define GYAddressRead  0x47
#define GYPowDown      0x00      //�ر�
#define GYPowOn        0x01      //��ģ��ȴ�����ָ��
#define GYReset        0x07      //�������ݼĴ���ֵ��PowerOnģʽ����Ч
#define GYHResMode     0x10      //�߷ֱ��� ��λ1lx ����ʱ��120ms
#define GYHResMode2    0x11      //�߷ֱ���ģʽ2 ��λ0.5lx ����ʱ��120ms
#define GYLResMode     0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms
#define OneGYHResMode  0x20      //һ�θ߷ֱ��� ���� ������ģ��ת�� PowerDownģʽ
#define OneGYHResMode2 0x21      //ͬ������
#define OneGYLResMode  0x23      // ������
/*************************************************************/
void gy30_set_mode(u8 command);
u16 gy30_read_data(void);
#endif
