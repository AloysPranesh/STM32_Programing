#include"uart.h"


#define GPIOAEN			(1U<<2)
#define UART2EN			(1U<<17)
#define UART1EN			(1U<<14)

#define CR1_RE_EN		(1U<<2)
#define CR1_TE_EN		(1U<<3)
#define CR1_UE_EN		(1U<<13)

#define SR_TXE			(1U<<7)
#define SR_RXNE			(1U<<5)

#define sys_freq		8000000
#define APB1_CLK		sys_freq

#define UART_BAUDRATE	9600

static void uart_set_baurd_rate(USART_TypeDef *USARTx, uint32_t periph_clk,uint32_t BaudRate);
static uint16_t compute_uart_BD (uint32_t periph_clk,uint32_t BaudRate);

void uart2_write(int tx_data);
void UART2_TX_init(void);

int __io_putchar(int tx_data)
{
	uart2_write(tx_data);
	uart1_write(tx_data);
	return tx_data;
}


void UART2_RXTX_init(void)
{
//********configure uart2 GPIOA pin*********//
	// enable clock access to GPIOA
	RCC->APB2ENR |= GPIOAEN;
	// set pa2 as alternate function mode
	GPIOA->CRL |= (1U<<8);
	GPIOA->CRL |= (1U<<9);
	GPIOA->CRL &=~(1U<<10);
	GPIOA->CRL |= (1U<<11);
	// set pa3 as alternate function mode
	GPIOA->CRL &=~ (1U<<12);
	GPIOA->CRL &=~ (1U<<13);
	GPIOA->CRL |=  (1U<<14);
	GPIOA->CRL &=~ (1U<<15);
	// set pa2 & pa3 alternate function type to UART2_TX & UART2_RX
	AFIO->MAPR &=~(1U<<3);
	//enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//configure baud rate
	uart_set_baurd_rate(USART2,APB1_CLK,UART_BAUDRATE);
	//configure the transfer direction
	USART2->CR1 = (CR1_TE_EN | CR1_RE_EN); // i am clearing everything in CR1 Register thats why didn't put(|) *OR* */
	//enable UART module
	USART2->CR1 |= CR1_UE_EN;
//*****************************************//
}

void UART1_RXTX_init(void)
{
//********configure uart2 GPIOA pin*********//
	// enable clock access to GPIOA
	RCC->APB2ENR |= GPIOAEN;
	// set pa9 as alternate function mode
	GPIOA->CRH |= (1U<<4);
	GPIOA->CRH |= (1U<<5);
	GPIOA->CRH &=~(1U<<6);
	GPIOA->CRH |= (1U<<7);
	// set pa10 as alternate function mode
	GPIOA->CRH &=~ (1U<<8);
	GPIOA->CRH &=~ (1U<<9);
	GPIOA->CRH |=  (1U<<10);
	GPIOA->CRH &=~ (1U<<11);
	// set pa9 & pa10 alternate function type to UART2_TX & UART2_RX
	AFIO->MAPR &=~(1U<<2);
	//enable clock access to UART1
	RCC->APB2ENR |= UART1EN;
	//configure baud rate
	uart_set_baurd_rate(USART1,APB1_CLK,UART_BAUDRATE);
	//configure the transfer direction
	USART1->CR1 = (CR1_TE_EN | CR1_RE_EN);
	//enable UART module
	USART1->CR1 |= CR1_UE_EN;
}

void UART2_TX_init(void)
{
//********configure uart2 GPIOA pin*********//
	// enable clock access to GPIOA
	RCC->APB2ENR |= GPIOAEN;
	// set pa2 as alternate function mode
	GPIOA->CRL |= (1U<<8);
	GPIOA->CRL |= (1U<<9);
	GPIOA->CRL &=~(1U<<10);
	GPIOA->CRL |= (1U<<11);
	// set pa2 alternate function type to UART2_TX
	AFIO->MAPR &=~(1U<<3);
	//enable clock access to UART2
	RCC->APB1ENR |= UART2EN;
	//configure baud rate
	uart_set_baurd_rate(USART2,APB1_CLK,UART_BAUDRATE);
	//configure the transfer direction
	USART2->CR1 |= CR1_TE_EN; // i am clearing everything in CR1 Register thats why didn't put(|) *OR* */
	//enable UART module
	USART2->CR1 |= CR1_UE_EN;
//*****************************************//
}

char uart2_read()
{
	//first make sure the receive data register is not empty
	while(!(USART2->SR & SR_RXNE)){}
	//Read Data
	return USART2->DR;
}

void uart2_write(int tx_data)
{
	//first make sure the transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}
	//write to transmit data register
	USART2->DR = (tx_data & 0xFF);

}


char uart1_read()
{
	//first make sure the receive data register is not empty
	while(!(USART1->SR & SR_RXNE)){}
	//Read Data
	return USART1->DR;
}

void uart1_write(int tx_data)
{
	//first make sure the transmit data register is empty
	while(!(USART1->SR & SR_TXE)){}
	//write to transmit data register
	USART1->DR = (tx_data & 0xFF);

}


static void uart_set_baurd_rate(USART_TypeDef *USARTx, uint32_t periph_clk,uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_BD(periph_clk,BaudRate);
}

static uint16_t compute_uart_BD (uint32_t periph_clk,uint32_t BaudRate)
{
	return((periph_clk+(BaudRate/2U))/BaudRate);
}
