#ifndef __IERG3810_TFT_LCD
#define __IERG3810_TFT_LCD
#include "stm32f10x.h"

void Print_Image_Basic(u16 start_x, u16 dlength_x, u16 start_y, u16 dlength_y, u8 par, u8 imageDir);
void IERG3810_TFTLCD_WrReg(u16 regval);
void IERG3810_TFTLCD_WrData(u16 data);
void IERG3810_TFTLCD_SetParameter(void);
void IERG3810_TFTLCD_Init(void);
void IERG3810_TFTLCD_DrawDot(u16 x, u16 y, u16 color);
void IERG3810_TFTLCD_FillRectangle(u16 color, u16 start_x, u16 dlength_x, u16 start_y, u16 dlength_y);
void IERG3810_TFTLCD_ShowChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_ShowCChar(u16 x, u16 y, u8 cchar, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_ShowCChar2(u16 x, u16 y, u8 cchar, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_SevenSegment(u16 color, u16 start_x, u16 start_y, u8 digit);
void IERG3810_EXP3_clear(void);
void IERG3810_TFTLCD_DrawPic(int height, int length,u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_DrawColorPic(int height, int length,u16 x, u16 y, u8 ascii);
void IERG3810_TFTLCD_DrawPic2(int height, int length,u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_DrawDotPic(int height, int length,u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_ShowChiChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor);
void IERG3810_TFTLCD_SevenSegment1(u16 color, u16 start_x, u16 start_y, u8 digit);

#endif
