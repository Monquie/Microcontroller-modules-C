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
void init()
{
    ADCON1 = 0x0F;     
    //NUTNHAN_IO = NHAP;  //Cac port led xuat
    row_io  =   XUAT;
    gcol_io =   XUAT;
    rcol_io =   XUAT;
	rowidx 	=	0;
}
const unsigned char maurom[FRAME][ROWMAX]={
    {0x01,0x02,0x3C,0x24,0x24,0x3C,0x40,0x80},
    {0x80,0x40,0x3C,0x24,0x24,0x3C,0x02,0x01}
};
unsigned char rambuf[FRAME][ROWMAX], rowidx;

void rom2ram()
{
    unsigned char i;
    for(i=0; i<COLMAX; i++)
    {
        rambuf[RED][i] = maurom[RED][i];
        rambuf[GREEN][i] = maurom[GREEN][i];
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
    while(1);
}