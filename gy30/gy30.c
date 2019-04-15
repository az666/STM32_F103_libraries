#include "gy30.h"

void gy30_set_mode(u8 command)
{
    do{
    iic_start();
    iic_byte_write(GYAddressWrite);
	}while(iic_wait_ack());
	iic_byte_write(command);
	iic_wait_ack();
	iic_stop();
}

u16 gy30_read_data(void)
{
	u16 buf;
	iic_start();
	iic_byte_write(GYAddressRead);
	iic_wait_ack();
	buf=iic_byte_read(1);
	buf=buf<<8;
	buf+=0x00ff&iic_byte_read(0);
	iic_stop();
	return buf;
}
