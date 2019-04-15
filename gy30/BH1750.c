#include "delay.h"
#include "BH1750.h"

void bh_data_send(u8 command)
{
    do{
    iic_start();
    iic_byte_write(BHAddWrite);
	}while(iic_wait_ack());
	iic_byte_write(command);
	iic_wait_ack();
	iic_stop();
}

u16 bh_data_read(void)
{
	u16 buf;
	iic_start();
	iic_byte_write(BHAddRead);
	iic_wait_ack();
	buf=iic_byte_read(1);
	buf=buf<<8;
	buf+=0x00ff&iic_byte_read(0);
	iic_stop();
	return buf;
}
