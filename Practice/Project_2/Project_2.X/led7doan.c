#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include"Timer.h"
volatile unsigned char led_en __at(0xF8A); //LATB
volatile unsigned char led_en_io __at(0xF93); //TRISB
volatile unsigned char red_io __at(0xF95); //TRISD
volatile unsigned char red __at(0xF8C); //LATD
#define MAX7S   16
#define SELMAX  4
#define	XUAT	0
#define	NHAP	1
unsigned char dbuf[SELMAX], selidx;
const unsigned char dl7doan[MAX7S]={
0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void init()
{
	ADCON1=0x0F;
	red_io	=	XUAT;
	led_en_io	=	XUAT;
}
unsigned char gm_7doan(unsigned char so)
{
    if (so>0x1F) return 0;
    if (so<0x10) return dl7doan[so];
    return d17doan[so&0x0F] | 0x80;
}
void timer_process()
{
    led_en = 0;
    red = gm_7doan(dbuf[selidx]);
    led_en = 1<<selidx++;
    selidx%=SELMAX;
}

void main()
{
    init();
    int0_init();
    while(1);
}