#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include"Timer.h"
volatile unsigned char row __at(0xF8A); //LATB
volatile unsigned char row_io __at(0xF93); //TRISB
volatile unsigned char gcol __at(0xF8B); //LATC
volatile unsigned char gcol_io __at(0xF94); //TRISC
volatile unsigned char rcol __at(0xF8C); //LATD
volatile unsigned char rcol_io __at(0xF95); //TRISD
#define XUAT        0
#define NHAP        1
#define NUTNHAN     PORTAbits.RA5
#define NUTNHAN_IO  TRISAbits.RA5
#define COLMAX  8
#define ROWMAX  8
#define FRAME   2
#define RED     0
#define GREEN   1
unsigned char rambuf[FRAME][ROWMAX], rowidx;
void init()
{
    ADCON1 = 0x0F;     
    NUTNHAN_IO = NHAP;  //Nhap
    row_io  =   XUAT;
    gcol_io =   XUAT;
    rcol_io =   XUAT;
	rowidx 	=	0;
}
const unsigned char maurom_v1[FRAME][ROWMAX]={
    {0xF1,0xA2,0xC4,0x88,0x11,0x23,0x45,0x8F},
    {0xF0,0xA0,0xC0,0x80,0x01,0x03,0x05,0x0F}
};
const unsigned char maurom_v2[FRAME][ROWMAX]={
	{0x0F,0x77,0x7B,0x7D,0xBE,0xDE,0xEE,0xF0},
	{0x0F,0x07,0x03,0x11,0x88,0xC0,0xE0,0xF0}
}

void rom2ram()
{
    unsigned char i;
    for(i=0; i<COLMAX; i++)
    {
        rambuf[RED][i] = maurom_v1[RED][i];
        rambuf[GREEN][i] = maurom_v1[GREEN][i];
    }
}
// thuc hien quy trình quét LED theo chi so rowidx
void timer_process()
{
    row = 0;                    //bo chon cac hang
    gcol=rambuf[GREEN][rowidx]; //xuat du lieu xanh
    rcol=rambuf[RED][rowidx];   //xuat du lieu do
    row=1<<rowidx++;            //chon hang theo rowidx
    rowidx%=ROWMAX;             //rowidx
}
void main()
{
    init();
    rom2ram();
	timer0_init();
    while(1){
		if(NUTNHAN == 0)
        {
			for(unsigned char i=0; i<COLMAX; i++)
			{
				rambuf[RED][i] = maurom_v2[RED][i];
				rambuf[GREEN][i] = maurom_v2[GREEN][i];
			}
            while(NUTNHAN == 0);
        }
	};
}