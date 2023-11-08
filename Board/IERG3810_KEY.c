#include "stm32f10x.h"
//#include "IERG3810_KEY.h"

// put your procedure and code here
	
void IERG3810_KEY_Init()
	{
			
		GPIOA->CRL &=0xFFFFFFF0;
		GPIOA->CRL |=0x00000008;
		GPIOA->BRR =1;
		
		GPIOE->CRL &=0xFFFF0FFF;
		GPIOE->CRL |=0x00008000;
		GPIOE->BSRR =1<<3;
		
		GPIOE->CRL &=0xFFFFF0FF;
		GPIOE->CRL |=0x00000800;
		GPIOE->BSRR =1<<2;
		
		
	}