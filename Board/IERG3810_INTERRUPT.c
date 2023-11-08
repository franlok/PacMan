#include "stm32f10x.h"
#include <stdlib.h>
#include "IERG3810_INTERRUPT.h"
#include "IERG3810_Delay.h"

u32 sheep	=0;
u32 timeout	=10000;
u32 ps2key	=0;
u32 ps2count	=0;
u32 ps2dataReady=0;
u8 receive=0x00;
u8 lastrecv=0x00;
u8 check;
Keypad *key;
int bitcount=-1;

void IERG3810_while_content(void)
{
		sheep++;
		if(ps2count >=11)
		{}
		if(timeout==0)
		{
			timeout=20000;
			ps2key=0;
			ps2count=0;
		}
		timeout--;
}

void EXTI2_IRQHandler(void)
{
	u8 i;
	for (i=0; i<10; i++)
	{
	GPIOB->BRR = 1<<5;
	Delay(1000000);
	GPIOB->BSRR = 1<<5;
	Delay(1000000);
	}
	EXTI->PR = 1<<2;
}
void EXTI0_IRQHandler(void)
{
	u8 i;
	for (i=0; i<10; i++)
	{
	GPIOE->BRR = 1<<5;
	Delay(1000000);
	GPIOE->BSRR = 1<<5;
	Delay(1000000);
	}
	EXTI->PR = 1<<0;
}

void IERG3810_NVIC_SetPriorityGroup(u8 prigroup)
{
	u32 temp, temp1;
	temp1 = prigroup & 0x00000007;
	temp1 <<= 8;
	temp = SCB->AIRCR;
	temp &= 0x0000F8FF;
	temp |= 0x05FA0000;
	temp |= temp1;
	SCB->AIRCR=temp;
}

void IERG3810_key2_ExtiInit(void)
{
	
	RCC->APB2ENR |= 1<<6;
	GPIOE->CRL &= 0XFFFFF0FF;
	GPIOE->CRL |= 0X00000800;
	GPIOE->ODR |= 1<<2;
	RCC->APB2ENR |= 0x01;
	AFIO->EXTICR[0] &= 0xFFFFF0FF;
	AFIO->EXTICR[0] |= 0x00000400;
	EXTI->IMR |= 1<<2;
	EXTI->FTSR |= 1<<2;

	NVIC->IP[8] = 0x65;
	NVIC->ISER[0] |= (1<<8);
}

void IERG3810_keyUP_ExtiInit(void)
{
	RCC->APB2ENR |= 1<<2;
	GPIOA->CRL &= 0XFFFFFFF0;
	GPIOA->CRL |= 0X00000008;
	GPIOA->ODR |= 0;
	RCC->APB2ENR |= 0x01;
	AFIO->EXTICR[0] &= 0xFFFFFFF0;
	AFIO->EXTICR[0] |= 0x00000000;
	EXTI->IMR |= 1;
	EXTI->FTSR |= 1;

	NVIC->IP[6] = 0x75;
	NVIC->ISER[0] |= (1<<6);
}

void IERG3810_PS2key_ExtiInit(void)
{
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRH &= 0XFFFF00FF;
	GPIOC->CRH |= 0X00008800;
	GPIOC->ODR |= 1<<11;
	RCC->APB2ENR |= 0x01;
	AFIO->EXTICR[2] &= 0xFFFF0FFF;
	AFIO->EXTICR[2] |= 0x00002000;
	EXTI->IMR |= 1<<11;
	EXTI->FTSR |= 1<<11;


	NVIC->IP[40] = 0x65;
	NVIC->ISER[1] |= (1<<8);

	key=(Keypad *)calloc(2,sizeof(Keypad));
	key[0]=keyEn, key[1]=keyEn;
}

void TRIGGER_BY_KEYPAD(u8 receive)
{
	if(receive==0x70){key[0]=key0;}
	if(receive==0x69){key[0]=key1;}
	if(receive==0x72){key[0]=key2;}
	if(receive==0x7A){key[0]=key3;}
	if(receive==0x6B){key[0]=key4;}
	if(receive==0x73){key[0]=key5;}
	if(receive==0x74){key[0]=key6;}
	if(receive==0x6C){key[0]=key7;}
	if(receive==0x75){key[0]=key8;}
	if(receive==0x7D){key[0]=key9;}
	if(receive==0x77){key[0]=keyNum;}
	if(receive==0x5A || lastrecv==0xE0){key[0]=keyEn;}
	if(key[0]==key6){PacDir[1]=1;}
	if(key[0]==key8){PacDir[1]=2;}
	if(key[0]==key4){PacDir[1]=3;}
	if(key[0]==key5){PacDir[1]=4;}
	if(key[0]==keyNum){}
	if(key[0]==keyEn || key[1]==keyNum)
	{}
	key[1]=key[0];
	key[0]=keyEn;
	lastrecv=receive;
}

void EXTI15_10_IRQHandler(void)
{

	
	if(EXTI->PR & (1<<11))
	{
		check=(GPIOC->IDR & (1<<10))?1:0;
		if(bitcount==-1)
		{
			if(!check)
			{
				receive=0x00;
				bitcount=0;
			}
		}
	else if (bitcount<8)
	{
		receive|=check<<bitcount;
		bitcount++;
	}
	else if(bitcount==8)
	{

		TRIGGER_BY_KEYPAD(receive);
		bitcount=-1;
	}
	Delay(10);
	EXTI->PR|=1<11;
	}		
}



