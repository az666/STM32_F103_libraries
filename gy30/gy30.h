#ifndef __GY30__H_
#define __GY30__H_
#include "iic.h"
#include "delay.h"
/*************************************************************/

#define GYAddressWrite 0x46
#define GYAddressRead  0x47
#define GYPowDown      0x00      //关闭
#define GYPowOn        0x01      //打开模块等待测量指令
#define GYReset        0x07      //重置数据寄存器值在PowerOn模式下有效
#define GYHResMode     0x10      //高分辨率 单位1lx 测量时间120ms
#define GYHResMode2    0x11      //高分辨率模式2 单位0.5lx 测量时间120ms
#define GYLResMode     0x13      //低分辨率 单位4lx 测量时间16ms
#define OneGYHResMode  0x20      //一次高分辨率 测量 测量后模块转到 PowerDown模式
#define OneGYHResMode2 0x21      //同上类似
#define OneGYLResMode  0x23      // 上类似
/*************************************************************/
void gy30_set_mode(u8 command);
u16 gy30_read_data(void);
#endif
