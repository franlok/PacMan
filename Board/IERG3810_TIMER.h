#ifndef __IERG3810_TIMER
#define __IERG3810_TIMER
#include "stm32f10x.h"

void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void IERG3810_TIM3_Init(u16 arr, u16 psc);
void IERG3810_TIM4_Init(u16 arr, u16 psc);
void IERG3810_SYSTICK_Init10ms(void);
void IERG3810_TIM3_PwmInit(u16 arr, u16 psc);
void IERG3810_TIM3_PwmInit_2(u16 arr, u16 psc);
void DS0_turnOff(void);
void DS0_turnOff2(void);
void IERG3810_EXP_5_6(void);
void IERG3810_PWM_DIR_EQUAL(u8 d);
void IERG3810_PWM_DIR_EQUAL_2(u8 d1, u8 d2, u8 d3);
void IERG3810_EXP_5_7_TASK1(void);
void IERG3810_EXP_5_7_TASK2(void);


#endif
