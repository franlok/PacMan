#define length_x 12
#define length_y 15
#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include "IERG3810_TFTLCD.h"
#include "IERG3810_MINI.h"
#include "IERG3810_MINI_MAP.h"
#include "IERG3810_Delay.h"


//Start of MapInfo

u8* pacStInit(u8 x, u8 y)
{
	u8* pac_st=(u8* )calloc(2, sizeof(u8));
	pac_st[0]=x;
	pac_st[1]=y;
	return pac_st;
}

MapEle* mapInfoInit(u8* pacman_st, u8** gosClu, u8** beanLoc)
{
	int i,j;
	u8 gosInd;
	MapEle *mapInfo=(MapEle *)calloc(length_x*length_y, sizeof(MapEle));
	for(j=0; j<15; j++)
	{
		for(i=0; i<12; i++)
		{
			if(*(map+i+j*12))
			{mapInfo[i+j*12]=wall;}
			else
			{mapInfo[i+j*12]=seed;Seed+=1;}
		}
	}
	mapInfo[(length_y-1)*length_x +pacman_st[0] -pacman_st[1]*length_x]=pacman;
	Seed-=1;
	for(i=0; i<flag2G; i++)
	{
		gosInd=(length_y-1)*length_x +gosClu[i][0] -gosClu[i][1]*length_x;
		Replace[i]=mapInfo[gosInd];
		mapInfo[gosInd]=ghost;
	}
	
	for(i=0; i<flag2G; i++)
	{
		GosMem[i]=setByValueII(GosClu[i], 2);
	}
	
	for(i=0; i<flag2N; i++)
	{
		mapInfo[(length_y-1)*length_x +beanLoc[i][0] -beanLoc[i][1]*length_x]=bean;
		Seed-=1;
	}
	return mapInfo;
}

void pacLocUpdate(u8* PacDir, u8* PacLoc, int LoopIndex)
{
	u8* tmp=malloc(2*sizeof(u8));
	u8 checkSpecial=checkEdgeAndDir(PacLoc, PacDir[LoopIndex]);
	tmp[0]=PacLoc[0];
	tmp[1]=PacLoc[1];
	if(checkSpecial)
	{	if(checkWall(specialSetAxis(tmp,checkSpecial)))
		{specialSetAxis(PacLoc,checkSpecial);PacDir[0]=PacDir[1];}
		else{pacLocUpdateII(PacDir,PacLoc);}
	}
	else
	{	setAxis(tmp,PacDir[LoopIndex]);
		if(checkWall(tmp))
		{setAxis(PacLoc,PacDir[LoopIndex]);PacDir[0]=PacDir[1];}
		else{pacLocUpdateII(PacDir,PacLoc);}
	}
	free(tmp);
}
void pacLocUpdateII(u8* PacDir, u8* PacLoc)
{
	u8* tmp=malloc(2*sizeof(u8));
	u8 LoopIndex=0;
	u8 checkSpecial=checkEdgeAndDir(PacLoc, PacDir[LoopIndex]);
	tmp[0]=PacLoc[0];
	tmp[1]=PacLoc[1];
	if(checkSpecial)
	{	if(checkWall(specialSetAxis(tmp,checkSpecial)))
		{specialSetAxis(PacLoc,checkSpecial);}
	}
	else
	{	setAxis(tmp,PacDir[LoopIndex]);
		if(checkWall(tmp))
		{setAxis(PacLoc,PacDir[LoopIndex]);}
	}
	free(tmp);
}

u8 checkWall(u8* PacLoc)
{
	if(GameMap[(length_y-1)*length_x +PacLoc[0] -PacLoc[1]*length_x]!=wall)
		return 1;
	else
		return 0;
}

void setAxis(u8* axis, u8 PacDir)
{
	if(PacDir==1){axis[0]+=1;}
	if(PacDir==2){axis[1]+=1;}
	if(PacDir==3){axis[0]-=1;}
	if(PacDir==4){axis[1]-=1;}
}

u16 checkEdgeAndDir(u8* PacLoc, u8 PacDir)
{
	u16 result=0;
	int index=(length_y-1)*length_x +PacLoc[0] -PacLoc[1]*length_x;
	if(index%12==11 && PacDir==1)
	{result=1;}
	if(index<length_x && PacDir==2)
	{result=2;}
	if(index%12==0 && PacDir==3)
	{result=3;}
	if(index>=length_x*(length_y-1) && PacDir==4)
	{result=4;}
	return result;
}
u8* specialSetAxis(u8* tmp, u8 checkSpecial)
{
	u8 result=checkSpecial;
	if(result==1){tmp[0]-=(length_x-1);}
	if(result==2){tmp[1]-=(length_y-1);}
	if(result==3){tmp[0]+=(length_x-1);}
	if(result==4){tmp[1]+=(length_y-1);}
	return tmp;
}

void mapInfoUpdate(MapEle* GameMap, u8* pacman_st, u8** gosClu, u8** gosMem)
{
	int i, j;
	u8 gosNew, gosOld, pacNew=(length_y-1)*length_x +pacman_st[0] -pacman_st[1]*length_x;
	
	for(j=0; j<15; j++)
	{
		for(i=0; i<12; i++)
		{
			if(*(GameMap+i+j*12)==pacman){*(GameMap+i+j*12)=empt;}
		}
	}
	if(Seed==0)
	{
		Win=1;
	}
	if(GameMap[pacNew]==seed)
	{Seed-=1;GPIOB->BSRR =1<<8;Delay(3000);GPIOB->BRR =1<<8;}
	if(GameMap[pacNew]==bean)
	{EatTime=40;SpTime=0;SpFlag=0;Score+=10;}//if(Life==0){Lost=1;}
	if(GameMap[pacNew]==ghost)
	{
		if(EatTime)
		{
			
			GosDead=20;
		}
		if(Replace[i]==seed)
			{
				Seed-=1;GPIOB->BSRR =1<<8;Delay(3000);GPIOB->BRR =1<<8;//
			}
	}
	GameMap[pacNew]=pacman;
	
	for(i=0; i<flag2G; i++)
	{
		gosOld=(length_y-1)*length_x +gosMem[i][0] -gosMem[i][1]*length_x;
		gosNew=(length_y-1)*length_x +gosClu[i][0] -gosClu[i][1]*length_x;
		GameMap[gosOld]=Replace[i];
		if(GameMap[gosNew]==pacman){if(!EatTime){SpTime=30;if(Score!=0){Score-=10;}}}//if(Life==0){Lost=1;}
		else{Replace[i]=GameMap[gosNew];}
		GameMap[gosNew]=ghost;
		GosMem[i][0]=GosClu[i][0];
		GosMem[i][1]=GosClu[i][1];
	}
	
}

u8* setByValueII(u8* arr, u8 num)
{
	int i;
	u8* tmp=(u8* )malloc(num*sizeof(u8));
	for(i=0; i<num; i++)
	{
		tmp[i]=arr[i];
	}
	return tmp;
}

void printMapInfo(MapEle *mapInfo, u8 pacFlash, u8 imageDir)
{
	int i,j;
	u8 tmp=rand();
	for(j=0; j<15; j++)
	{
		for(i=0; i<12; i++)
		{
			if(*(mapInfo+i+j*12)==wall)
			IERG3810_TFTLCD_FillRectangle(0xffff, 20*i, 20, 300-20*j, 20);
			else
			if(*(mapInfo+i+j*12)==seed)
			{IERG3810_TFTLCD_DrawDotPic(20, 20, 20*i, 300-20*j, tmp%3, 0xFFE0, 0);tmp+=1;}
			else
			if(*(mapInfo+i+j*12)==empt)
			IERG3810_TFTLCD_FillRectangle(0x0000, 20*i, 20, 300-20*j, 20);
			else
			if(*(mapInfo+i+j*12)==ghost)
				if(GosDead)
				{Print_Image_Basic(20*i, 20, 300-20*j, 20, 8, 1);}
					else
					{Print_Image_Basic(20*i, 20, 300-20*j, 20, 5, 1);}
			else
			if(*(mapInfo+i+j*12)==bean)
			Print_Image_Basic(20*i, 20, 300-20*j, 20, 7, 1);
			else
			if(*(mapInfo+i+j*12)==pacman)
			{if(EatTime)
				{Print_Image_Basic(20*i, 20, 300-20*j, 20, 4, imageDir);}
			 else
			 {
					if(SpFlag)
					{IERG3810_TFTLCD_FillRectangle(0x0000, 20*i, 20, 300-20*j, 20);}
					else
					{Print_Image_Basic(20*i, 20, 300-20*j, 20, 2+pacFlash, imageDir);}
			 }
			}
			
		}
	}
}

//End of MapInfo

