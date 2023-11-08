#ifndef __IERG3810_INTERRUPT
#define __IERG3810_INTERRUPT
#include "stm32f10x.h"
typedef enum {key0, key1, key2, key3, key4, key5, key6, key7, key8, key9, keyNum, keyEn } Keypad;

extern u32 sheep;
extern u32 timeout;
extern u32 ps2key;
extern u32 ps2count;
extern u32 ps2dataReady;
extern u8 receive;
extern u8 lastrecv;
extern u8 check;
extern int bitcount;



extern Keypad *key;


//should be separated
extern u8*		PacDir;

void IERG3810_while_content(void);
void EXTI2_IRQHandler(void);
void EXTI0_IRQHandler(void);
void IERG3810_NVIC_SetPriorityGroup(u8 prigroup);
void IERG3810_key2_ExtiInit(void);
void IERG3810_keyUP_ExtiInit(void);
void IERG3810_PS2key_ExtiInit(void);
void LED_ON_OFF(u8 receive);
void EXTI15_10_IRQHandler(void);

#endif
