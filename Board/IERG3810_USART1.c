#include "stm32f10x.h"
#include "IERG3810_USART1.h"


void IERG3810_USART1_init(u32 pclk2, u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk2*1000000)/(bound*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
		mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR |=1<<2;
	RCC->APB2ENR |=1<<14;
	GPIOA->CRH &=0xFFFFF00F;
	GPIOA->CRH |=0x000008B0;
	RCC->APB2RSTR |=1<<14;
	RCC->APB2RSTR &=~(1<<14);
	USART1->BRR  =mantissa;
	USART1->CR1 |=0x2008;
}