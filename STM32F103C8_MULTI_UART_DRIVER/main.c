#include <stdio.h>
#include <stdint.h>
#include "stm32f103x6.h"
#include "uart.h"


char gps_data;

int main(void)
{
	UART2_RXTX_init();
	UART1_RXTX_init();
	while(1)
	{
		gps_data = uart1_read();
		uart2_write(gps_data);
	}
}




