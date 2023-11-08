#define NotExist 99
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stm32f10x.h"
#include "IERG3810_LED.h"
#include "IERG3810_clock.h"
#include "IERG3810_TFTLCD.h"
#include "IERG3810_Buzzer.h"
#include "IERG3810_Delay.h"
#include "IERG3810_USART1.h"
#include "IERG3810_USART2.h"
#include "IERG3810_USART_print.h"
#include "IERG3810_INTERRUPT.h"
#include "IERG3810_TIMER.h"
#include "IERG3810_MINI.H"
#include "IERG3810_MINI_MAP_III.H"
#include "IERG3810_MINI_MAP_IV.H"
#include "IERG3810_MINI_TABLE_FULL.H"
#include "IERG3810_MINI_TABLE_BRIEF.H"



u8** gosCluInit(u8 num);
void gosAdd(u8 x, u8 y);
//
int		i;
u8* 	addPath2BriefII(u8* verLoc, u8 Dir);
void 	subAddPath2BriefII(u8* cur, u8 Dir, u8* result);
u8 		oppDirII(u8 Dir);
u8 		loc2VertII(u8* Loc);
u8 		isPassingEdgeII(u8* axis, u8 Dir);
void 	setAxis2II(u8* axis, u8 Dir);
u8* 	specialSetAxisII(u8* axis, u8 Dir);
u8 		notWallII(u8* axis, u8 Dir);

u8 		requestShortestPathDir(void);
u8 		IsPacOnVert(u8* srcInfo);
u8 		IsGosOnVert(u8* srcInfo);
u8 		getShortestPath4In1(u8* PacInfo, u8* GosInfo);
u8 		IsInSameScope(u8* PacInfo, u8* GosInfo);
u8* 	setLoc(u8 x, u8 y);

u8** 	beanInit(u8 num);
void 	beanAdd(u8 x, u8 y);
u8 		escapeDir(u8 curDir);
u8* 	ranInit(void);
u8 		requestShortestPathDirII(void);
u8 		getShortestPath4In1II(u8* PacInfo, u8* GosInfo);
void 	gosCluUpdate(u8* looptmp);
u8		testing(u8* looptmp, u8 i, u8 par);
void 	testing4(u8 i);
int task1HeartBeat;




MapEle* GameMap;
u8* 		PacLoc;
u8*			PacDir;
u8			Seed;
u8 			pacFlash;
//
u8*			PacSt;
u8* 		GosLoc;
u8**		GosClu;
MapEle* Replace;
u8**		BeanLoc;
u8			SpFlag;
u8			SpTime;
u8			flag2G;
u8			flag2N;
u8			flag2B;
u8			EatTime;
u8*			RAN;
u8*			RANFlag;
u8**		GosMem;
u8*			Looptmp;
u8			GosDead;

u8			RANE;
u8			Win;
u8			WinFlag;
u8			Lost;
u8			Life;
u8			Score;
u8			Second;
u8			SFlag;



int main(void)
{
	u8 t1,t2,t3;
	u8 g1,g2,g3;
	IERG3810_clock_tree_init();
	IERG3810_LED_Init();
	IERG3810_Buzzer_Init();
	IERG3810_TFTLCD_Init();
	IERG3810_PS2key_ExtiInit();
	IERG3810_NVIC_SetPriorityGroup(5);
	IERG3810_TIM3_Init(4999, 7199);
	IERG3810_SYSTICK_Init10ms();
	IERG3810_USART2_init(36, 9600);


	pacFlash=1;
	Seed		=0;
	SpTime	=0;
	SpFlag	=0;
	EatTime	=0;
	flag2G	=0;
	flag2N	=0;
	flag2B	=20;
	Looptmp	=(u8*)calloc(4,sizeof(u8));
	PacSt		=pacStInit(1,1);
	PacLoc	=pacStInit(1,1);
	PacDir	=pacStInit(0,0);
	BeanLoc	=beanInit(4);
	beanAdd(1,13);
	beanAdd(1,2);
	beanAdd(10,13);
	beanAdd(10,1);
	GosClu	=gosCluInit(5);
	gosAdd(2,13);
	GosLoc	=GosClu[0];
	Replace	=(MapEle* )calloc(flag2G,sizeof(MapEle));
	RAN			=ranInit();
	RANFlag	=(u8* )calloc(flag2G,sizeof(u8));
	GosMem	=(u8**)malloc(flag2G*sizeof(u8*));
	Win			=0;
	WinFlag	=0;
	RANE=rand();
	Lost=0;
	Score=100;
	Second=0;
	SFlag=0;
	
//cover page
	while(1){
		int PressStart = 0;
		if(PressStart == 1) break;
		Delay(8000000);
		IERG3810_TFTLCD_FillRectangle(0, 0, 240, 0, 320);
		IERG3810_TFTLCD_DrawPic(150, 150, 20, 150, 0, 0, 0xFFE0);
		IERG3810_TFTLCD_DrawPic2(50, 50, 150, 125, 0, 0, 0xFFFF);
		IERG3810_TFTLCD_DrawPic2(50, 50, 190, 125, 0, 0, 0x001F);
			IERG3810_TFTLCD_ShowChar(80, 100, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(88, 100, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(96, 100, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(104, 100, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(112, 100, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(120, 100, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(128, 100, 55, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(136, 100, 51, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(144, 100, 50, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(152, 100, 48, 0xFFFF, 0);
		
			IERG3810_TFTLCD_ShowChar(80, 70, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(88, 70, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(96, 70, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(104, 70, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(112, 70, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(120, 70, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(128, 70, 53, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(136, 70, 54, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(144, 70, 49, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(152, 70, 51, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChiChar(70, 100, 0, 0xFFFF, 0); 
			IERG3810_TFTLCD_ShowChiChar(54, 100, 1, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChiChar(38, 100, 2, 0xFFFF, 0);
			
			IERG3810_TFTLCD_ShowChiChar(38, 70, 5, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChiChar(54, 70, 4, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChiChar(70, 70, 3, 0xFFFF, 0);
			IERG3810_TFTLCD_ShowChar(38, 40,48+32, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8, 40,82+32, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*2, 40,69+32, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*3, 40,115, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*4, 40,115, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*6, 40,34, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*7, 40,75, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*8, 40,69, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*9, 40,89, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*10, 40,50, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*11, 40,34, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*13, 40,84, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*14, 40,111, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*16, 40,83, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*17, 40,116, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*18, 40,97, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*19, 40,114, 0xFFE0, 0);
			IERG3810_TFTLCD_ShowChar(38+8*20, 40,116, 0xFFE0, 0);
		if (GPIOE->IDR & GPIO_Pin_2) {
				;
		}
		else {
			PressStart = 1;
		}
		if(PressStart == 1) break;
	}
	
	
	while(1)
	{
		Delay(8000000);
		IERG3810_TFTLCD_FillRectangle(0, 0, 240, 0, 320);
		IERG3810_TFTLCD_ShowChar(8, 320-16*2, 73, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*2, 320-16*2, 110, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*3, 320-16*2, 115, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*4, 320-16*2, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*5, 320-16*2, 114, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*6, 320-16*2, 117, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*7, 320-16*2, 99, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*8, 320-16*2, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*9, 320-16*2, 105, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*10, 320-16*2, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*11, 320-16*2, 110, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*12, 320-16*2, 58, 0xFFE0, 0);
		
		IERG3810_TFTLCD_ShowChar(8, 320-16*3, 67, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*2, 320-16*3, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*3, 320-16*3, 110, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*4, 320-16*3, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*5, 320-16*3, 114, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*6, 320-16*3, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*7, 320-16*3, 108, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*9, 320-16*3, 80, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*10, 320-16*3, 97, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*11, 320-16*3, 99, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*12, 320-16*3, 45, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*13, 320-16*3, 77, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*14, 320-16*3, 97, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*15, 320-16*3, 110, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*16, 320-16*3, 46, 0xFFE0, 0);
		
		IERG3810_TFTLCD_ShowChar(8, 320-16*4, 89, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*2, 320-16*4, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*3, 320-16*4, 117, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*5, 320-16*4, 109, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*6, 320-16*4, 117, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*7, 320-16*4, 115, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*8, 320-16*4, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*10, 320-16*4, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*11, 320-16*4, 97, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*12, 320-16*4, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*14, 320-16*4, 97, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*15, 320-16*4, 108, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*16, 320-16*4, 108, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*18, 320-16*4, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*19, 320-16*4, 104, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*20, 320-16*4, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*22, 320-16*4, 100, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*23, 320-16*4, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*24, 320-16*4, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*25, 320-16*4, 115, 0xFFE0, 0);
		
		IERG3810_TFTLCD_ShowChar(8, 320-16*5, 105, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*2, 320-16*5, 110, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*3, 320-16*5, 115, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*4, 320-16*5, 105, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*5, 320-16*5, 100, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*6, 320-16*5, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*8, 320-16*5, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*9, 320-16*5, 104, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*10, 320-16*5, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*12, 320-16*5, 109, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*13, 320-16*5, 97, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*14, 320-16*5, 112, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*16, 320-16*5, 119, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*17, 320-16*5, 104, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*18, 320-16*5, 105, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*19, 320-16*5, 108, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*20, 320-16*5, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*22, 320-16*5, 97, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*23, 320-16*5, 118, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*24, 320-16*5, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*25, 320-16*5, 105, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*26, 320-16*5, 100, 0xFFE0, 0);
		
		IERG3810_TFTLCD_ShowChar(8, 320-16*6, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*2, 320-16*6, 104, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*3, 320-16*6, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*5, 320-16*6, 99, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*6, 320-16*6, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*7, 320-16*6, 108, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*8, 320-16*6, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*9, 320-16*6, 114, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*10, 320-16*6, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*11, 320-16*6, 100, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*13, 320-16*6, 103, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*14, 320-16*6, 104, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*15, 320-16*6, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*16, 320-16*6, 115, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*17, 320-16*6, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*18, 320-16*6, 46, 0xFFE0, 0);
		
		IERG3810_TFTLCD_ShowChar(8, 320-16*8, 85, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*2, 320-16*8, 112, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*3, 320-16*8, 58, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*4, 320-16*8, 56, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*6, 320-16*8, 68, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*7, 320-16*8, 111, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*8, 320-16*8, 119, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*9, 320-16*8, 110, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*10, 320-16*8, 58, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*11, 320-16*8, 53, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*13, 320-16*8, 76, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*14, 320-16*8, 101, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*15, 320-16*8, 102, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*16, 320-16*8, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*17, 320-16*8, 58, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*18, 320-16*8, 52, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*20, 320-16*8, 82, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*21, 320-16*8, 105, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*22, 320-16*8, 103, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*23, 320-16*8, 104, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*24, 320-16*8, 116, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*25, 320-16*8, 58, 0xFFE0, 0);
		IERG3810_TFTLCD_ShowChar(8*26, 320-16*8, 54, 0xFFE0, 0);
		
		for(i = 5; i>0; i--){
			
			
			IERG3810_TFTLCD_FillRectangle(0, 80, 80, 32, 160 );
			IERG3810_TFTLCD_SevenSegment1(0xFFFF, 80, 32, i);
			Delay(8000000);
		}
		break;
	}
	
	//
	GameMap	=mapInfoInit(PacLoc, GosClu, BeanLoc);
	//End
	
	while(1)
	{	
		

		if(1)
		{
			if(1)
			{

		if(task1HeartBeat>=100){task1HeartBeat=0;Second+=1;}
		
		
		if(task1HeartBeat%16==4 )
		{	if(pacFlash==1){pacFlash=0;}else{pacFlash=1;}
			printMapInfo(GameMap, pacFlash, (PacDir[0]?PacDir[0]:1));	
		}
		if(EatTime==0)
		if(task1HeartBeat%16==8)
		{
			if(SpTime)
			{if(SpFlag){SpFlag=0;}else{SpFlag=1;}SpTime-=1;}
			printMapInfo(GameMap, pacFlash, (PacDir[0]?PacDir[0]:1));	
		}

		
		if(task1HeartBeat%16==8)
		{
			printMapInfo(GameMap, pacFlash, (PacDir[0]?PacDir[0]:1));
			if(EatTime){EatTime-=1;}
			if(EatTime>0)
			pacLocUpdate(PacDir, PacLoc, 1); 
			mapInfoUpdate(GameMap,PacLoc,GosClu,GosMem );
			t1=(Seed/100)%10, t2=(Seed/10)%10, t3=Seed%10;
		}


		
		if(task1HeartBeat%32==16)
		{	
			printMapInfo(GameMap, pacFlash, (PacDir[0]?PacDir[0]:1));
			if(EatTime==0)
			pacLocUpdate(PacDir, PacLoc, 1); 
			if(GosDead)
			{GosDead-=1;}
			else
			{testing(Looptmp, 0, 0);}
			mapInfoUpdate(GameMap,PacLoc,GosClu, GosMem);
			t1=(Seed/100)%10, t2=(Seed/10)%10, t3=Seed%10;
		}

		g1=(Score/100)%10, g2=(Score/10)%10, g3=Score%10;
		IERG3810_TFTLCD_ShowChar(0,  0,83, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(8,  0,67, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(16, 0,79, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(24, 0,82, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(32, 0,69, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(40, 0,58, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(48, 0,48+g1, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(56, 0,48+g2, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(64, 0,48+g3, 0xFCA0, 0);
		
		IERG3810_TFTLCD_ShowChar(80, 0,32+51, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(88, 0,32+69, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(96, 0,32+69, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(104, 0,32+68, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(112, 0,58, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(120, 0,48+t1, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(128, 0,48+t2, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(136, 0,48+t3, 0xFCA0, 0);
		
		IERG3810_TFTLCD_ShowChar(152, 0, 84, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(160, 0, 105, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(168, 0, 109, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(176, 0, 101, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(184, 0, 58, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(192, 0, 48+(Second/100)%10, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(200, 0, 48+(Second/10)%10, 0xFCA0, 0);
		IERG3810_TFTLCD_ShowChar(208, 0, 48+(Second)%10, 0xFCA0, 0);
		
		}
		else
		{
			if(WinFlag==0)
			{
			IERG3810_TFTLCD_FillRectangle(0,0,240,0,320);
			WinFlag=1;
			}
			IERG3810_TFTLCD_ShowChar(50+0, 120,89, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+8, 120,111, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+16, 120,117, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+24, 120,32, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+32, 120,87, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+40, 120,105, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+48, 120,110, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+56, 120,33, 65049, 0);
		}
		}
		else
		{
			IERG3810_TFTLCD_ShowChar(50+0, 120,89, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+8, 120,111, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+16, 120,117, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+24, 120,32, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+32, 120,32+44, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+40, 120,111, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+48, 120,115, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+56, 120,116, 65049, 0);
			IERG3810_TFTLCD_ShowChar(50+56, 120,33, 65049, 0);
		}
		if(Seed==0) 	break;
	}
	
while(1){
	
		int PressStart = 0;
		if(PressStart == 1) break;
		Delay(8000000);
	USART_print(2, "Show score: 140");
		
	if(receive==0x69){key[0]=key1;NVIC_SystemReset();break;}
	IERG3810_TFTLCD_ShowChar(50-16, 190,89, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(58-16, 190,79, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(66-16, 190,85, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(82-16, 190,87, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(90-16, 190,73, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(98-16, 190,78, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(106-16, 190,33, 0xFFE0, 0);
	
	IERG3810_TFTLCD_ShowChar(50-16, 170, 84, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(58-16, 170, 105, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(66-16, 170, 109, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(74-16, 170, 101, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(82-16, 170, 58, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(90-16, 170, 48+(Second/100)%10, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(98-16, 170, 48+(Second/10)%10, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(106-16, 170, 48+(Second)%10, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(114-16, 170, 115, 0xFFE0, 0);
	
	
	IERG3810_TFTLCD_ShowChar(50-16, 150,67, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(58-16, 150,111, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(66-16, 150,110, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(74-16, 150,103, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(82-16, 150,114, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(90-16, 150,97, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(98-16, 150,116, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(106-16, 150,117, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(114-16, 150,108, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(122-16, 150,97, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(130-16, 150,116, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(138-16, 150,105, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(146-16, 150,111, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(154-16, 150,110, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(162-16, 150,115, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(180-16, 150,33, 0xFFE0, 0);
	
	IERG3810_TFTLCD_ShowChar(50-16, 130,48+32, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8-16, 130,82+32, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*2-16, 130,69+32, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*3-16, 130,115, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*4-16, 130,115, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*6-16, 130,34, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*7-16, 130,75, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*8-16, 130,69, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*9-16, 130,89, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*10-16, 130,50, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*11-16, 130,34, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*13-16, 130,84, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*14-16, 130,111, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*16-16, 130,82, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*17-16, 130,101, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*18-16, 130,115, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*19-16, 130,116, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*20-16, 130,97, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*21-16, 130,114, 0xFFE0, 0);
	IERG3810_TFTLCD_ShowChar(50+8*22-16, 130,116, 0xFFE0, 0);
	
		if (GPIOE->IDR & GPIO_Pin_2) {
				;
		}
		else {
			PressStart = 1;
		}
		if(PressStart == 1) break;
	}
	
	


	

}

u8* ranInit(void)
{
	int i;
	u8* result=(u8* )calloc(flag2G,sizeof(u8));
	for(i=0; i<flag2G; i++){result[i]=rand();}
	return result;
}

u8** gosCluInit(u8 num)
{
	int i=0;
	u8** row=(u8** )malloc(num*sizeof(u8*));
	for(i=0; i<num; i++)
	{
		u8* col=(u8* )malloc(2*sizeof(u8));
		row[i]=col;
	}
	return row;
}
void gosAdd(u8 x, u8 y)
{
	if(flag2G<5)
	{
		GosClu[flag2G][0]=x;
		GosClu[flag2G][1]=y;
		flag2G+=1;
	}	
}

u8 testing(u8* looptmp, u8 i, u8 par)
{
	int j;
	u8 tmp=0, result=0, rant=0;
	srand(rand()*rand());
	GosLoc=GosClu[i];
				for(j=1; j<=4; j++){if(notWallII(GosLoc, j)){looptmp[tmp]=j;tmp+=1;}}
				//
				rant=rand();
				result=looptmp[rant%tmp];if(par){return result;}
				setAxis2II(GosClu[i], result);
				return 0;
				
}
void testing4(u8 i)
{
		u8 result=0;
		GosLoc=GosClu[i];
		result=requestShortestPathDir();
		setAxis2II(GosClu[i], result);
}
void gosCluUpdate(u8* looptmp)
{
	int i, j;
	u8 result=0, tmp=0;
	if(0)
	if(EatTime)
	{
		for(i=0; i<flag2G; i++)
		{
			GosLoc=GosClu[i];
			tmp=requestShortestPathDir();
			result=escapeDir(tmp);
			setAxis2II(GosClu[i], result);
		}
		return;
	}
	if(0)
	if(SpTime)
	{
		for(i=0; i<flag2G; i++)
		{
			GosLoc=GosClu[i];
			for(j=1; j<=4; j++){if(notWallII(GosLoc, j)){looptmp[tmp]=j;tmp+=1;}}
			result=looptmp[rand()%tmp];
			setAxis2II(GosClu[i], result);
			tmp=0;
		}
		return ;
	}
	if(EatTime==0 && SpTime==0)
	{
		for(i=0; i<flag2G; i++)
		{
			GosLoc=GosClu[i];
			if(RANFlag[i]==0){RAN[i]=rand()%3;RANFlag[i]=10;}else{RANFlag[i]-=1;}
			if(RAN[i]==0)
			{
				for(j=1; j<=4; j++){if(notWallII(GosLoc, i)){looptmp[tmp]=i;tmp+=1;}}
				result=looptmp[rand()%tmp];
				setAxis2II(GosClu[i], result);
				tmp=0;
			}
			if(RAN[i]==1)
			{
				result=requestShortestPathDir();
				setAxis2II(GosClu[i], result);
			}
			if(RAN[i]==2)
			{
				setAxis2II(GosClu[i], result);
			}
		}
			
	}
}
u8** beanInit(u8 num)
{
	int i=0;
	u8** row=(u8** )malloc(num*sizeof(u8*));
	for(i=0; i<num; i++)
	{
		u8* col=(u8* )malloc(2*sizeof(u8));
		row[i]=col;
	}
	return row;
}

void beanAdd(u8 x, u8 y)
{
	if(flag2N<4)
	{
		BeanLoc[flag2N][0]=x;
		BeanLoc[flag2N][1]=y;
		flag2N+=1;
	}	
}
u8 escapeDir(u8 curDir)
{
	int i=0;
	u8 result;
	for(i=1; i<=4; i++)
	{if(notWallII(GosLoc, i)){if(i!=curDir){result=i;}}}
	return result;
}

u8 IsInSameScope(u8* PacInfo, u8* GosInfo)
{
	u8 i=0, tmp=0, result=0, com1=0, com2=0;
	u8* PacTmp=setByValueII(PacInfo,6);
	u8* GosTmp=setByValueII(GosInfo,6);
	if(PacTmp[1]==GosTmp[1] && PacTmp[4]==GosTmp[4])
	{com1=1;}
	if(PacTmp[1]==GosTmp[4] && PacTmp[4]==GosTmp[1])
	{com2=1;}
	if(com1 || com2)
	{
		if(PacTmp[1]>PacTmp[4])
		{
			for(i=0; i<3; i++)
			{tmp=PacTmp[i];PacTmp[i]=PacTmp[i+3];PacTmp[i+3]=tmp;}
		}
		if(GosTmp[1]>GosTmp[4])
		{
			for(i=0; i<3; i++)
			{tmp=GosTmp[i];GosTmp[i]=GosTmp[i+3];GosTmp[i+3]=tmp;}
		}
		if(GosTmp[0]<PacTmp[0])
			result=GosTmp[5];
		else
			result=GosTmp[2];
	}
	free(PacTmp);
	free(GosTmp);
	return result;
}

u8 requestShortestPathDir(void)
{
	u8 result=0, PacOn=0, GosOn=0, spcheck=0;
	u8* PacInfo=(u8* )malloc(6*sizeof(u8));
	u8* GosInfo=(u8* )malloc(6*sizeof(u8));
	PacOn=IsPacOnVert(PacInfo);
	GosOn=IsGosOnVert(GosInfo);
	spcheck=IsInSameScope(PacInfo, GosInfo);
	if(spcheck)
	{return spcheck;}
	if(PacOn!=99)
	{	if(GosOn!=99)
		{result=tableFull[GosOn][PacOn][1];
		}
		else
		{ if(GosInfo[1]==NotExist){if(GosInfo[0]!=NotExist)return GosInfo[2];}
			if(GosInfo[4]==NotExist){if(GosInfo[3]!=NotExist)return GosInfo[5];}
			if((GosInfo[0]+tableFull[GosInfo[1]][PacOn][0])<(GosInfo[3]+tableFull[GosInfo[4]][PacOn][0]))
			{result=GosInfo[2];}else{result=GosInfo[5];}
		}
	}
	else
	{	if(GosOn!=99)
		{	if((PacInfo[0]+tableFull[GosOn][PacInfo[1]][0])<(PacInfo[3]+tableFull[GosOn][PacInfo[4]][0]))
			{result=tableFull[GosOn][PacInfo[1]][1];}else{result=tableFull[GosOn][PacInfo[4]][1];}
		}
		else
		{	if(GosInfo[1]==NotExist){if(GosInfo[0]!=NotExist)return GosInfo[2];}
			if(GosInfo[4]==NotExist){if(GosInfo[3]!=NotExist)return GosInfo[5];}
			result=getShortestPath4In1(PacInfo, GosInfo);
		}
	}
	free(PacInfo);
	free(GosInfo);
	return result;
}

u8 getShortestPath4In1(u8* PacInfo, u8* GosInfo)
{
	int i=0;
	u8* paths=(u8* )malloc(4*sizeof(u8));
	u8 result, tmpLen=99, tmpInd=99, P1=PacInfo[0], P2=PacInfo[3], G1=GosInfo[0], G2=GosInfo[3];
	u8 P1_G1=tableFull[PacInfo[1]][GosInfo[1]][0], P1_G2=tableFull[PacInfo[1]][GosInfo[4]][0], P2_G1=tableFull[PacInfo[4]][GosInfo[1]][0], P2_G2=tableFull[PacInfo[4]][GosInfo[4]][0];
	paths[0]=P1+P1_G1+G1;
	paths[1]=P1+P1_G2+G2;
	paths[2]=P2+P2_G1+G1;
	paths[3]=P2+P2_G2+G2;
	for(i=0; i<4; i++)
	{if(paths[i]<tmpLen){tmpLen=paths[i]; tmpInd=i;}}
	if(tmpInd==0 || tmpInd==2)
	{result=GosInfo[2];}
	else
	{result=GosInfo[5];}
	return result;
}



u8 IsPacOnVert(u8* srcInfo)
{
	int i;
	u8 result=0, vert=0, flag=0;
	u8* tmp;
	vert=loc2VertII(PacLoc);
	if(vert!=NotExist){result=vert;}
	else
	{	for(i=0; i<6; i++){srcInfo[i]=99;}
		for(i=1; i<=4; i++)
		{	if(notWallII(PacLoc, i))
			{tmp=addPath2BriefII(PacLoc, i);
				srcInfo[flag*3+0]=tmp[0];
				srcInfo[flag*3+1]=tmp[1];
				srcInfo[flag*3+2]=i;
				flag++;
				if(flag>1)
				break;
			}
		}
		if(srcInfo[1]==99 || srcInfo[4]==99)
		{if(srcInfo[1]==99){result=srcInfo[4];}else{result=srcInfo[1];}}
		else
		{result=99;}
	}
	free(tmp);
	return result;
}

u8 IsGosOnVert(u8* srcInfo)
{
	int i;
	u8 result=0, vert=0, flag=0;
	u8* tmp;
	vert=loc2VertII(GosLoc);
	IERG3810_TFTLCD_ShowChar(0,  0,48+vert/10, 65049, 0);
	IERG3810_TFTLCD_ShowChar(8,  0,48+vert%10, 65049, 0);
	if(vert!=NotExist){result=vert;
		IERG3810_TFTLCD_ShowChar(56,  0,48+vert/10, 65049, 0);
		IERG3810_TFTLCD_ShowChar(64,  0,48+vert%10, 65049, 0);
	}
	else
	{
		for(i=0; i<6; i++){srcInfo[i]=99;}
		for(i=1; i<=4; i++)
		{
			if(notWallII(GosLoc, i))
			{
				tmp=addPath2BriefII(GosLoc, i);
				srcInfo[flag*3+0]=tmp[0];
				srcInfo[flag*3+1]=tmp[1];
				srcInfo[flag*3+2]=i;
				flag++;
				if(flag>1)
				break;
			}
		}
		result=99;
	}
	free(tmp);
	return result;
}

u8* setLoc(u8 x, u8 y)
{
	u8* tmp=(u8* )malloc(2*sizeof(u8));
	tmp[0]=x;
	tmp[1]=y;
	return tmp;
}

u8* addPath2BriefII(u8* verLoc, u8 Dir)
{
	int i;
	u8 passingEdge=0, pathNum=0, outDir=Dir, inDir=0;
	u8* result=(u8* )calloc(2, sizeof(u8));
	u8* cur=setByValueII(verLoc, 2);
	passingEdge=isPassingEdgeII(cur, outDir);
	if(passingEdge)
	{
		specialSetAxisII(cur,outDir);
		inDir=oppDirII(outDir), outDir=0;
		pathNum=map4[cur[1]][cur[0]];
		if(pathNum<=2)
		{
			
			if(pathNum==2)
			{
				result[0]++;
				for(i=1; i<=4; i++)
				{if(notWallII(cur, i)){if(i!=inDir){outDir=i;break;}}}
				subAddPath2BriefII(cur, outDir, result);
			}
			else
			{
				
				result[0]++;
				result[1]=NotExist;
			}
		}
		else
		{
			result[0]++;
			result[1]=loc2VertII(cur);
		}
	}
	else
	{
		setAxis2II(cur,Dir);
		inDir=oppDirII(outDir), outDir=0;
		pathNum=map4[cur[1]][cur[0]];
		if(pathNum<=2)
		{
			
			if(pathNum==2)
			{
				result[0]++;
				for(i=1; i<=4; i++)
				{if(notWallII(cur, i)){if(i!=inDir){outDir=i;break;}}}
				subAddPath2BriefII(cur, outDir, result);
			}
			else
			{
				
				result[0]++;
				result[1]=NotExist;
			}
		}
		else
		{
			result[0]++;
			result[1]=loc2VertII(cur);
		}
	}
	free(cur);
	return result;
}

void subAddPath2BriefII(u8* cur, u8 Dir, u8* result)
{
	
	int i;
	u8 passingEdge=0, pathNum=0, outDir=Dir, inDir=0;
	passingEdge=isPassingEdgeII(cur, outDir);
	if(passingEdge)
	{
		specialSetAxisII(cur,outDir);
		inDir=oppDirII(outDir), outDir=0;
		pathNum=map4[cur[1]][cur[0]];
		if(pathNum<=2)
		{
			if(pathNum==2)
			{
				result[0]++;
				for(i=1; i<=4; i++)
				{if(notWallII(cur, i)){if(i!=inDir){outDir=i;break;}}}
				subAddPath2BriefII(cur, outDir, result);
			}
			else
			{
				result[0]++;
				result[1]=NotExist;
			}
		}
		else
		{
			result[0]++;
			result[1]=loc2VertII(cur);
		}
	}
	else
	{
		setAxis2II(cur,Dir);
		inDir=oppDirII(outDir), outDir=0;
		pathNum=map4[cur[1]][cur[0]];
		if(pathNum<=2)
		{
			if(pathNum==2)
			{
				result[0]++;
				for(i=1; i<=4; i++)
				{if(notWallII(cur, i)){if(i!=inDir){outDir=i;break;}}}
				subAddPath2BriefII(cur, outDir, result);
			}
			else
			{
				result[0]++;
				result[1]=NotExist;
			}
		}
		else
		{
			result[0]++;
			result[1]=loc2VertII(cur);
		}
	}
	
}

u8 oppDirII(u8 Dir)
{
	u8 result=0;
	if(Dir==1){result=3;}
	if(Dir==2){result=4;}
	if(Dir==3){result=1;}
	if(Dir==4){result=2;}
	return result;
}
u8 loc2VertII(u8* Loc)
{
	int j=0;
	for(j=0; j<flag2B; j++)
	{
		if(tableBrief[j][0][0]==Loc[0])
		{
			if(tableBrief[j][0][1]==Loc[1])
			return j;
		}
	}
	return NotExist;
}

u8 isPassingEdgeII(u8* axis, u8 Dir)
{
	u8 result=0;
	u16 edge=map3[axis[1]][axis[0]];
	if(edge)
	{	if(edge%10==1 && Dir==1)		{result=1;}
		if((edge/10)%10==1 && Dir==2)	{result=2;}
		if((edge/100)%10==1 && Dir==3)	{result=3;}
		if((edge/1000)%10==1 && Dir==4)	{result=4;}
	}
	return result;
}

void setAxis2II(u8* axis, u8 Dir)
{
	if(isPassingEdgeII(axis, Dir))
	{
		if(Dir==1){axis[0]-=(length_x-1);}
		if(Dir==2){axis[1]-=(length_y-1);}
		if(Dir==3){axis[0]+=(length_x-1);}
		if(Dir==4){axis[1]+=(length_y-1);}
	}
	else
	{
		if(Dir==1){axis[0]+=1;}
		if(Dir==2){axis[1]+=1;}
		if(Dir==3){axis[0]-=1;}
		if(Dir==4){axis[1]-=1;}
	}

}
u8* specialSetAxisII(u8* axis, u8 Dir)
{
	if(Dir==1){axis[0]-=(length_x-1);}
	if(Dir==2){axis[1]-=(length_y-1);}
	if(Dir==3){axis[0]+=(length_x-1);}
	if(Dir==4){axis[1]+=(length_y-1);}
	return axis;
}

u8 notWallII(u8* axis, u8 Dir)
{
	u8 result=0;
	u8* tmp=setByValueII(axis,2);
	if(isPassingEdgeII(tmp, Dir))
	{
		if(Dir==1){tmp[0]-=(length_x-1);}
		if(Dir==2){tmp[1]-=(length_y-1);}
		if(Dir==3){tmp[0]+=(length_x-1);}
		if(Dir==4){tmp[1]+=(length_y-1);}
	}
	else
	{
		if(Dir==1){tmp[0]+=1;}
		if(Dir==2){tmp[1]+=1;}
		if(Dir==3){tmp[0]-=1;}
		if(Dir==4){tmp[1]-=1;}
	}
	result=map4[tmp[1]][tmp[0]];
	free(tmp);
	return result;
}







