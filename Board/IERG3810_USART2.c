#include "stm32f10x.h"
#include "IERG3810_USART2.h"


void IERG3810_USART2_init(u32 pclk1, u32 bound)
{
	float temp;
	u16 mantissa;
	u16 fraction;
	temp=(float)(pclk1*1000000)/(bound*16);
	mantissa=temp;
	fraction=(temp-mantissa)*16;
		mantissa<<=4;
	mantissa+=fraction;
	RCC->APB2ENR |=1<<2;
	RCC->APB1ENR |=1<<17;
	GPIOA->CRL &=0xFFFF00FF;
	GPIOA->CRL |=0x00008B00;
	RCC->APB1RSTR |=1<<17;
	RCC->APB1RSTR &=~(1<<17);
	USART2->BRR  =mantissa;
	USART2->CR1 |=0x2008;
}