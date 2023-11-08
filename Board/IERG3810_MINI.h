#ifndef __IERG3810_MINI
#define __IERG3810_MINI

#include "stm32f10x.h"


typedef 	enum{empt,wall,seed,pacman,ghost,bean,ghost_dead} MapEle;

extern 		MapEle* GameMap;
extern 		u8* 		PacLoc;
extern 		u8*			PacDir;
extern 		u8			Seed;
extern 		u8 			pacFlash;
extern 		u8*			PacSt;//
extern 		u8*			GosLoc;
extern 		u8**		GosClu;
extern		u8**		GosMem;
extern 		u8**		BeanLoc;
extern 		u8			SpFlag;
extern 		u8			SpTime;
extern 		u8			flag2G;
extern 		u8			flag2N;
extern 		u8			EatTime;
extern		MapEle*	Replace;
extern 		u8*			RAN;
extern 		u8*			RANFlag;
extern		u8*			Looptmp;
extern		u8			GosDead;
extern		u8			Win;
extern		u8			Lost;
extern		u8			Life;
extern		u8			Score;
extern		u8			Second;
extern 		u8			SFlag;

MapEle* mapInfoInit(u8* pacman_st, u8** gosClu, u8** beanLoc);
void 		mapInfoUpdate(MapEle* GameMap, u8* pacman_st, u8** gosClu, u8** gosMem);
void 		pacLocUpdate(u8* PacDir, u8* PacLoc, int LoopIndex);
void 		pacLocUpdateII(u8* PacDir, u8* PacLoc);
void 		setAxis(u8* axis, u8 PacDir);
u8* 		specialSetAxis(u8* tmp, u8 checkSpecial);
u8 			checkWall(u8* PacLoc);
u16 		checkEdgeAndDir(u8* PacLoc, u8 PacDir);
void 		printMapInfo(MapEle *mapInfo, u8 pacFlash, u8 imageDir);
u8*			pacStInit(u8 x, u8 y);

u8* 		setByValueII(u8* arr, u8 num);


#endif
