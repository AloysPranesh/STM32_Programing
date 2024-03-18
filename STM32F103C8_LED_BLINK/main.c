//LED PORT AND PIN : PC13
#include<stdint.h>
#define PERIPH_BASE			(0x40000000UL)
#define APB2PERIPH_OFFSET 	(0x00010000UL)
#define APB2PERIPH_BASE 	(PERIPH_BASE + APB2PERIPH_OFFSET)
#define AHBPERIPH_OFFSET	(0x00018000UL)
#define AHBPERIPH_BASE		(PERIPH_BASE + AHBPERIPH_OFFSET)
#define GPIOC_OFFSET		(0x1000UL) // (0x0000 1000UL)
#define GPIOC_BASE			(APB2PERIPH_BASE + GPIOC_OFFSET)
#define RCC_OFFSET			(0x9000UL) // (0x0000 9000UL)
#define RCC_BASE			(AHBPERIPH_BASE + RCC_OFFSET)
#define GPIOCEN 			(1U<<4) // 0000 0000 0000 0000 0000 0000 0001 0000
#define PIN13				(1U<<13)
#define LED_PIN				PIN13
#define __IO 				volatile // instead of volatile we can use __IO

typedef struct
{
	volatile uint32_t dummy1;
	volatile uint32_t CRH;
	volatile uint32_t dummy2;
	volatile uint32_t ODR;
}GPIO_typedef;

typedef struct
{
	volatile uint32_t dummy[6];     // other registers are not need for this application
	volatile uint32_t APB2ENR;		// RCC_APB2ENR Register 	address offset 0x18
}RCC_typedef;

#define RCC		((RCC_typedef*)RCC_BASE)
#define GPIOC	((GPIO_typedef*)GPIOC_BASE)

int main(void)
{

	RCC->APB2ENR |= GPIOCEN;
	GPIOC->CRH |= (1U<<20);
	GPIOC->CRH |= (1U<<21);
	GPIOC->CRH &=~(1U<<22);
	GPIOC->CRH &=~(1U<<23);

	while(1)
	{
		GPIOC->ODR ^= LED_PIN;
		for( int i=0;i<1000000;i++){}
	}
}




