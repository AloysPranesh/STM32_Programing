#include<stdint.h>
#include "stm32f103x6.h"

void UART2_TX_init(void);
void uart2_write(int tx_data);
void UART2_RXTX_init(void);
char uart2_read();

void UART1_RXTX_init(void);
char uart1_read();
void uart1_write(int tx_data);
