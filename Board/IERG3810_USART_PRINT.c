#include "stm32f10x.h"
#include "IERG3810_USART_PRINT.h"

void USART_print(u8 USARTport, char *st)
{
	u8 i=0;
	while(st[i]!=0x00)
	{
		if(USARTport==1)
		{
			
			USART1->DR=st[i];
			while(USART1->SR>>7!=1){}
		
		}
		if(USARTport==2)
		{
			
			USART2->DR=st[i];
			while(USART2->SR>>7!=1){}
		
		}
		//Delay(50000);
		
		if(i==255)
		{
			break;
		}
		i++;
	}
}