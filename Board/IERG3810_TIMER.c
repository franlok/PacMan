#include "stm32f10x.h"
#include "IERG3810_TIMER.h"
#include "IERG3810_Delay.h"

u16 led0pwmval	=0;
u8  dir		=1;

void TIM3_IRQHandler(void)
{
	if(TIM3->SR & 1<<0)
	{
		
	}
	TIM3->SR &= ~(1<<0);
	
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR & 1<<0)
	{
		GPIOE->ODR ^= 1<<5;
	}
	TIM4->SR &= ~(1<<0);
}

void IERG3810_TIM3_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR	|=1<<1;
	TIM3->ARR	=arr;
	TIM3->PSC	=psc;
	TIM3->DIER	|=1<<0;
	TIM3->CR1	|=0x01;
	NVIC->IP[29]	=0x45;
	NVIC->ISER[0]	|=(1<<29);
}

void IERG3810_TIM4_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR	|=1<<2;//done
	TIM4->ARR	=arr;
	TIM4->PSC	=psc;
	TIM4->DIER	|=1<<0;
	TIM4->CR1	|=0x01;
	NVIC->IP[30]	=0x45;
	NVIC->ISER[0]	|=(1<<30);
}


void IERG3810_SYSTICK_Init10ms(void)
{
	SysTick->CTRL	=0;
	SysTick->LOAD	=89999;
	SysTick->CTRL &=~(1<<2);
	SysTick->CTRL |=1<<1;
	SysTick->CTRL |=1<<0;
}


void IERG3810_TIM3_PwmInit(u16 arr, u16 psc)
{
	RCC->APB2ENR	|=1<<3;
	GPIOB->CRL	&=0xFF0FFFFF;
	GPIOB->CRL	|=0x00B00000;

	RCC->APB2ENR	|=1<<0;
	AFIO->MAPR	&=0xFFFFF3FF;
	AFIO->MAPR	|=1<<11;

	RCC->APB1ENR	|=1<<1;
	TIM3->ARR	=arr;
	TIM3->PSC	=psc;
	TIM3->CCMR1	|=7<<12;
	TIM3->CCMR1	|=1<<11;
	TIM3->CCER	|=1<<4;
	TIM3->CR1	=0x0080;
	TIM3->CR1	|=0x01;
}

void IERG3810_TIM3_PwmInit_2(u16 arr, u16 psc)
{
	RCC->APB2ENR	|=1<<3;
	GPIOB->CRL	&=0xFF0FFFFF;
	GPIOB->CRL	|=0x00B00000;
	RCC->APB2ENR|=1<<0;
	RCC->APB2ENR|=1<<4;
	
	GPIOC->CRL	&=0x00FFFFFF;
	GPIOC->CRL	|=0xBB000000;
	GPIOC->CRH	&=0xFFFFFFF0;
	GPIOC->CRH	|=0x0000000B;
	
	RCC->APB2ENR	|=1<<0;
	AFIO->MAPR	&=0xFFFFF3FF;
	AFIO->MAPR	|=1<<11;
	AFIO->MAPR	|=1<<10;

	RCC->APB1ENR	|=1<<1;
	TIM3->ARR	=arr;
	TIM3->PSC	=psc;
	
	TIM3->CCMR1	|=7<<4;
	TIM3->CCMR1	|=1<<3;
	TIM3->CCMR1	|=7<<12;
	TIM3->CCMR1	|=1<<11;
	TIM3->CCMR2	|=7<<4;
	TIM3->CCMR2	|=1<<3;
	
	TIM3->CCER	|=1<<0;
	TIM3->CCER	|=1<<4;
	TIM3->CCER	|=1<<8;
	
	TIM3->CR1	=0x0080;
	TIM3->CR1	|=0x01;
}



void DS0_turnOff(void)
{
	GPIOB->BSRR	=1<<5;
}

void DS0_turnOff2(void)
{
	DS0_turnOff();
}

void IERG3810_EXP_5_6(void)
{
	Delay(1500);
		if(dir)
		{
			led0pwmval++;
		}
		else
		{
			led0pwmval--;
		}
		if(led0pwmval>5000)
		{
			dir=0;
		}
		if(led0pwmval==0)
		{
			dir=1;
		}
		TIM3->CCR2=led0pwmval;
}

void IERG3810_PWM_DIR_EQUAL(u8 d)
{
	u16 flag=1;
	u16 value;
	if(d){value=0;}
	else {value=5000;}
	while(flag<5000)
	{
		Delay(1500);
		if(d)
		{
			value++;
		}
		else
		{
			value--;
		}
		TIM3->CCR2=value;
		flag++;
	}
}
void IERG3810_PWM_DIR_EQUAL_2(u8 d1, u8 d2, u8 d3)
{
	u16 flag=1;
	u16 value1;
	u16 value2;
	u16 value3;
	if(d1)
	{
		if(d1==1) {value1=0;}
		else {value1=5000;}
	}
	if(d2)
	{
		if(d2==1) {value2=0;}
		else {value2=5000;}
	}
	if(d3)
	{
		if(d3==1) {value3=0;}
		else {value3=5000;}
	}
	while(flag<5000)
	{
		Delay(1500);
		if(d1)
		{
			if(d1==1) {value1++;}
			else {value1--;}
		}
		if(d2)
		{
			if(d2==1) {value2++;}
			else {value2--;}
		}
		if(d3)
		{
			if(d3==1) {value3++;}
			else {value3--;}
		}
		if(d1){TIM3->CCR1=value1;}
		if(d2){TIM3->CCR2=value2;}
		if(d3){TIM3->CCR3=value3;}
		flag++;
	}
	
}
void IERG3810_EXP_5_7_TASK1(void)
{
		IERG3810_PWM_DIR_EQUAL_2(1,0,0);
	while(1)
	{
		IERG3810_PWM_DIR_EQUAL_2(0,1,0);
		IERG3810_PWM_DIR_EQUAL_2(-1,0,0);
		IERG3810_PWM_DIR_EQUAL_2(0,0,1);
		IERG3810_PWM_DIR_EQUAL_2(0,-1,0);
		IERG3810_PWM_DIR_EQUAL_2(1,0,0);
		IERG3810_PWM_DIR_EQUAL_2(0,0,-1);
	}
}

void IERG3810_EXP_5_7_TASK2(void)
{
		IERG3810_PWM_DIR_EQUAL_2(1,0,0);
		IERG3810_PWM_DIR_EQUAL_2(-1,0,0);
		IERG3810_PWM_DIR_EQUAL_2(1,1,0);
		IERG3810_PWM_DIR_EQUAL_2(-1,-1,0);
		IERG3810_PWM_DIR_EQUAL_2(0,1,0);
		IERG3810_PWM_DIR_EQUAL_2(0,-1,0);
		IERG3810_PWM_DIR_EQUAL_2(0,1,1);
		IERG3810_PWM_DIR_EQUAL_2(0,-1,-1);
		IERG3810_PWM_DIR_EQUAL_2(0,0,1);
		IERG3810_PWM_DIR_EQUAL_2(0,0,-1);
		IERG3810_PWM_DIR_EQUAL_2(1,0,1);
		IERG3810_PWM_DIR_EQUAL_2(-1,0,-1);
}
