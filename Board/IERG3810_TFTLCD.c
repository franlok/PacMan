#include "stm32f10x.h"
#include "IERG3810_TFTLCD.h"
#include "FONT.H"
//#include "CFONT.h"
//#include "CHINESE.H"
#include "IERG3810_MINI_IMAGE.H"


typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;

#define LCD_BASE	((u32) (0x6C000000 | 0x000007FE))
#define LCD		((LCD_TypeDef *) LCD_BASE)


void Print_Image_Basic(u16 start_x, u16 dlength_x, u16 start_y, u16 dlength_y, u8 par, u8 imageDir)
{
	int i=0, j=0;
	unsigned short *image;
	if(par==1){image=image01;}
	if(par==2){image=image02;}
	if(par==3){image=image03;}
	if(par==4){image=image04;}
	if(par==5){image=image05;}
	if(par==6){image=image06;}
	if(par==7){image=image07;}
	if(par==8){image=image08;}
	if(par==9){image=image09;}
	if(par==10){image=image10;}
	if(par==11){image=image11;}
	
	IERG3810_TFTLCD_WrReg(0x2A);
		IERG3810_TFTLCD_WrData(start_x>>8);
		IERG3810_TFTLCD_WrData(start_x & 0xFF);
		IERG3810_TFTLCD_WrData((dlength_x + start_x - 1) >>8);
		IERG3810_TFTLCD_WrData((dlength_x + start_x - 1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
		IERG3810_TFTLCD_WrData(start_y>>8);
		IERG3810_TFTLCD_WrData(start_y & 0xFF);
		IERG3810_TFTLCD_WrData((dlength_y + start_y - 1) >>8);
		IERG3810_TFTLCD_WrData((dlength_y + start_y - 1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C);
	
	if(imageDir==1)
		for(i=0; i<dlength_x * dlength_y; i++)
			IERG3810_TFTLCD_WrData(image[i]);
	if(imageDir==2)
		for(j=0; j<dlength_y; j++)
			for(i=0; i<dlength_x;i++)
				IERG3810_TFTLCD_WrData(image[i*dlength_x+j]);	
	if(imageDir==3)
		for(j=0; j<dlength_y; j++)
			for(i=0; i<dlength_x;i++)
				IERG3810_TFTLCD_WrData(image[(j+1)*dlength_x-i-1]);
	if(imageDir==4)
		for(j=0; j<dlength_y; j++)
			for(i=0; i<dlength_x;i++)
				IERG3810_TFTLCD_WrData(image[(i+1)*dlength_x-j-1]);
}


void IERG3810_TFTLCD_WrReg(u16 regval)
{
	LCD->LCD_REG=regval;
}

void IERG3810_TFTLCD_WrData(u16 data)
{
	LCD->LCD_RAM=data;
}

void IERG3810_TFTLCD_SetParameter(void)
{
	IERG3810_TFTLCD_WrReg(0x01);
	IERG3810_TFTLCD_WrReg(0x11);

	IERG3810_TFTLCD_WrReg(0x3A);
	IERG3810_TFTLCD_WrData(0x55);

	IERG3810_TFTLCD_WrReg(0x29);

	IERG3810_TFTLCD_WrReg(0x36);
	IERG3810_TFTLCD_WrData(0xCA);
}

void IERG3810_TFTLCD_Init(void)
{
	RCC->AHBENR	|=1<<8;
	RCC->APB2ENR	|=1<<3;
	RCC->APB2ENR	|=1<<5;
	RCC->APB2ENR	|=1<<6;
	RCC->APB2ENR	|=1<<8;
	GPIOB->CRL	&=0xFFFFFFF0;
	GPIOB->CRL	|=0x00000003;

	GPIOD->CRH	&=0x00FFF000;
	GPIOD->CRH	|=0xBB000BBB;
	GPIOD->CRL	&=0xFF00FF00;
	GPIOD->CRL	|=0x00BB00BB;

	GPIOE->CRH	&=0x00000000;
	GPIOE->CRH	|=0xBBBBBBBB;
	GPIOE->CRL	&=0x0FFFFFFF;
	GPIOE->CRL	|=0xB0000000;

	GPIOG->CRH	&=0xFFF0FFFF;
	GPIOG->CRH	|=0x000B0000;
	GPIOG->CRL	&=0xFFFFFFF0;
	GPIOG->CRL	|=0x0000000B;

	FSMC_Bank1->BTCR[6]	=0x00000000;
	FSMC_Bank1->BTCR[7]	=0x00000000;
	FSMC_Bank1E->BWTR[6]	=0x00000000;
	FSMC_Bank1->BTCR[6]	|=1<<12;
	FSMC_Bank1->BTCR[6]	|=1<<14;
	FSMC_Bank1->BTCR[6]	|=1<<4;
	FSMC_Bank1->BTCR[7]	|=0<<28;
	FSMC_Bank1->BTCR[7]	|=1<<0;
	FSMC_Bank1->BTCR[7]	|=0xF<<8;
	FSMC_Bank1E->BWTR[6]	|=0<<28;
	FSMC_Bank1E->BWTR[6]	|=0<<0;
	FSMC_Bank1E->BWTR[6]	|=3<<8;
	FSMC_Bank1->BTCR[6]	|=1<<0;
	IERG3810_TFTLCD_SetParameter();
	GPIOB->ODR	|=1<<0;
	

}


void IERG3810_TFTLCD_DrawDot(u16 x, u16 y, u16 color)
{
	IERG3810_TFTLCD_WrReg(0x2A);
		IERG3810_TFTLCD_WrData(x>>8);
		IERG3810_TFTLCD_WrData(x & 0xFF);
		IERG3810_TFTLCD_WrData(0x01);
		IERG3810_TFTLCD_WrData(0x3F);
	IERG3810_TFTLCD_WrReg(0x2B);
		IERG3810_TFTLCD_WrData(y>>8);
		IERG3810_TFTLCD_WrData(y & 0xFF);
		IERG3810_TFTLCD_WrData(0x01);
		IERG3810_TFTLCD_WrData(0xDF);
	IERG3810_TFTLCD_WrReg(0x2C);
		IERG3810_TFTLCD_WrData(color);
}

void IERG3810_TFTLCD_FillRectangle(u16 color, u16 start_x, u16 dlength_x, u16 start_y, u16 dlength_y)
{
	u32 index=0;
	IERG3810_TFTLCD_WrReg(0x2A);
		IERG3810_TFTLCD_WrData(start_x>>8);
		IERG3810_TFTLCD_WrData(start_x & 0xFF);
		IERG3810_TFTLCD_WrData((dlength_x + start_x - 1) >>8);
		IERG3810_TFTLCD_WrData((dlength_x + start_x - 1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
		IERG3810_TFTLCD_WrData(start_y>>8);
		IERG3810_TFTLCD_WrData(start_y & 0xFF);
		IERG3810_TFTLCD_WrData((dlength_y + start_y - 1) >>8);
		IERG3810_TFTLCD_WrData((dlength_y + start_y - 1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C);
	for(index=0; index<dlength_x * dlength_y; index++)
	{
		IERG3810_TFTLCD_WrData(color);
	}
		
}

void IERG3810_TFTLCD_ShowChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor)
{
	u8 i, j;
	u8 index;
	u8 height=16, length=8;
	if(ascii<32 || ascii>127)
		return;
	ascii-=32;
	IERG3810_TFTLCD_WrReg(0x2A);
		IERG3810_TFTLCD_WrData(x>>8);
		IERG3810_TFTLCD_WrData(x & 0xFF);
		IERG3810_TFTLCD_WrData((length + x - 1) >>8);
		IERG3810_TFTLCD_WrData((length + x - 1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
		IERG3810_TFTLCD_WrData(y>>8);
		IERG3810_TFTLCD_WrData(y & 0xFF);
		IERG3810_TFTLCD_WrData((height + y - 1) >>8);
		IERG3810_TFTLCD_WrData((height + y - 1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C);	
	for(j=0; j<height/8; j++)
	{
		for(i=0; i<height/2; i++)
		{
			for(index=0; index<length; index++)
			{
				if((asc2_1608[ascii][index*2+1-j]>>i) & 0x01)
					IERG3810_TFTLCD_WrData(color);
				else
					IERG3810_TFTLCD_WrData(bgcolor);
			}
		}
	}
}
void IERG3810_TFTLCD_DrawPic(int height, int length,u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor)
{
	int i,j;
	u8 index;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x>>8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((length + x -1) >> 8);
	IERG3810_TFTLCD_WrData((length + x -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y>>8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((height + y -1) >> 8);
	IERG3810_TFTLCD_WrData((height + y -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C);
	
	for (j = height-1; j >=0 ; j--)
	{
		for (i = 0; i < length; i++)
		{
			if ((pic[i+j*length]) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			
		}
	}
}

void IERG3810_TFTLCD_DrawPic2(int height, int length,u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor)
{
	int i,j;
	u8 index;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x>>8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((length + x -1) >> 8);
	IERG3810_TFTLCD_WrData((length + x -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y>>8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((height + y -1) >> 8);
	IERG3810_TFTLCD_WrData((height + y -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C);
	
	for (j = height-1; j >=0 ; j--)
	{
		for (i = 0; i < length; i++)
		{
			if ((pic2[i+j*length]) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			
		}
	}
}

void IERG3810_TFTLCD_DrawDotPic(int height, int length,u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor)
{
	int i,j;
	u8 index;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x>>8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((length + x -1) >> 8);
	IERG3810_TFTLCD_WrData((length + x -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y>>8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((height + y -1) >> 8);
	IERG3810_TFTLCD_WrData((height + y -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C); 
	
	for (j = height-1; j >=0 ; j--)
	{
		for (i = 0; i < length; i++)
		{
			if (ascii == 0){
			if ((DotPic1[i+j*length]) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
			
						if (ascii == 1){
			if ((DotPic2[i+j*length]) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
			
			
						if (ascii == 2){
			if ((DotPic3[i+j*length]) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
		}
	}
}

void IERG3810_TFTLCD_DrawColorPic(int height, int length,u16 x, u16 y, u8 ascii)
{
	int i,j;
	u8 index;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x>>8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((length + x -1) >> 8);
	IERG3810_TFTLCD_WrData((length + x -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y>>8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((height + y -1) >> 8);
	IERG3810_TFTLCD_WrData((height + y -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C); 
	
	for (j = height-1; j >=0 ; j--)
	{
		for (i = 0; i < length; i++)
		{
			IERG3810_TFTLCD_WrData(pic[i+j*length]);
			
		}
	}
}

void IERG3810_TFTLCD_SevenSegment1(u16 color, u16 start_x, u16 start_y, u8 digit)
{
	if(digit == 0){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+10, 55 ); //e
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+75, 55 ); //f
	}
	if(digit == 1){
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	}
	if(digit == 2){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+10, 55 ); //e
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	}
	if(digit == 3){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	}
	if(digit == 4){
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+75, 55 ); //f
	}
	if(digit == 5){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+75, 55 ); //f
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	}
	if(digit == 6){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+10, 55 ); //e
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+75, 55 ); //f
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	}
	if(digit == 7){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	}
	if(digit == 8){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+10, 55 ); //e
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+75, 55 ); //f
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	}
	if(digit == 9){
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+130, 10 ); //a
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+75, 55 ); //b
	IERG3810_TFTLCD_FillRectangle(color, start_x+65, 10, start_y+10, 55 ); //c
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y, 10 ); //d
	IERG3810_TFTLCD_FillRectangle(color, start_x, 10, start_y+75, 55 ); //f
	IERG3810_TFTLCD_FillRectangle(color, start_x+10, 55, start_y+65, 10 ); //g
	}
}

void IERG3810_TFTLCD_SevenSegment(u16 color, u16 start_x, u16 start_y, u8 digit)
{
	u8 ssd[10][7]={
	{1,1,1,1,1,1,0},
	{0,1,1,0,0,0,0},
	{1,1,0,1,1,0,1},
	{1,1,1,1,0,0,1},
	{0,1,1,0,0,1,1},
	{1,0,1,1,0,1,1},
	{1,0,1,1,1,1,1},
	{1,1,1,0,0,0,0},
	{1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1}};
	
	u8 ss[8][4]={
	{10,55,130,10},	//a
	{65,10,75,55},	//b
	{65,10,10,55},	//c
	{10,55,0,10},	//d
	{0,10,10,55},	//e
	{0,10,75,55},	//f
	{10,55,65,10}};	//g

	u8 index=0;
	for(index=0; index<7; index++)
	{
		if(ssd[digit][index])
		{
			IERG3810_TFTLCD_FillRectangle(color,ss[index][0]+start_x,ss[index][1],ss[index][2]+start_y,ss[index][3]);
		}
	}
}

void IERG3810_TFTLCD_ShowChiChar(u16 x, u16 y, u8 ascii, u16 color, u16 bgcolor)
{
	u8 i,j;
	u8 index;
	u8 height=16, length=16;
	IERG3810_TFTLCD_WrReg(0x2A);
	IERG3810_TFTLCD_WrData(x>>8);
	IERG3810_TFTLCD_WrData(x & 0xFF);
	IERG3810_TFTLCD_WrData((length + x -1) >> 8);
	IERG3810_TFTLCD_WrData((length + x -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2B);
	IERG3810_TFTLCD_WrData(y>>8);
	IERG3810_TFTLCD_WrData(y & 0xFF);
	IERG3810_TFTLCD_WrData((height + y -1) >> 8);
	IERG3810_TFTLCD_WrData((height + y -1) & 0xFF);
	IERG3810_TFTLCD_WrReg(0x2C); 
	
	for (j = 0; j < height/8; j++)
	{
		for (i = 0; i < height/2; i++)
		{
			for (index=0; index<length; index++)
			{
			if ((asc2_1616[ascii][index*2+1-j]>>i) & 0x01) IERG3810_TFTLCD_WrData(color);
				else IERG3810_TFTLCD_WrData(bgcolor);
			}
		}
	}
}

void IERG3810_EXP3_clear(void)
{
	IERG3810_TFTLCD_FillRectangle(0,0,400,0,400);
	
}
