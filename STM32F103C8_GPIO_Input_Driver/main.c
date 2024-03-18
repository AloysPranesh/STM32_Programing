#include "stm32f103x6.h"

#define PIN_PA8		(1U<<8)  // IDR Register - shifting 1  on 8th bit
#define PUSH_PIN	PIN_PA8

int main(void)
{
	//enabling port A and C because led in PC13 push button in PA8
	RCC->APB2ENR |= (1U<<4);
	RCC->APB2ENR |= (1U<<2);
	//PC13 is LED setting it as output mode
	GPIOC->CRH |= (1U<<20);
	GPIOC->CRH |= (1U<<21);
	GPIOC->CRH &=~(1U<<22);
	GPIOC->CRH &=~(1U<<23);

	//PA8 is push button setting it as output mode
	GPIOA->CRH &=~ (1U<<0);
	GPIOA->CRH &=~ (1U<<1);
	GPIOA->CRH |=  (1U<<2);
	GPIOA->CRH &=~ (1U<<3);

	while(1)
	{
		if(GPIOA->IDR & PUSH_PIN)
			{
			GPIOC->BSRR |= (1U<<13);
			}
		else
			{
			GPIOC->BSRR |= (1U<<29);
			}
	}
}
