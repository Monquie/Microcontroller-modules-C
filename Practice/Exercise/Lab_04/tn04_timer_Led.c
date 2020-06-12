#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include "Timer.h"
#define _XTAL_FREQ 10000000
// Dinh nghia du lieu ROM
#define MAXIDX 8
#define MAXROM 4
const unsigned char dl_rom[MAXROM][MAXIDX] ={
    {0xFF,0x7E,0x3C,0x18,0x00,0x18,0x3C,0x7E},
    {0x01,0x03,0x07,0x1F,0x1F,0x3F,0x7F,0xFF},
    {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80},
    {0x81,0xC3,0xE7,0xFF,0xFF,0xE7,0xC3,0x81},};
#define XUAT 0
#define NHAP 1
#define SODEM500MS 50
unsigned char dem500ms;
unsigned char dl_ram[MAXIDX],ramidx,romidx,so_ql;
volatile unsigned char led __at(0xF8c);
volatile unsigned char led_io __at(0xF95);
void doi_ql()
{
    unsigned char i;
    for(i=0;i<MAXIDX;i++){
        dl_ram[i]=dl_rom[romidx][i];
        romidx++;
        romidx%=MAXROM;
    }
}
void xuatled()
{
    led = dl_ram[ramidx++];
    ramidx%=MAXIDX;
}
void timer_process()
{
    if((--dem500ms)==0)
    {
		doi_ql();
        xuatled();
        dem500ms = SODEM500MS;
    }
}
void init()
{
    ADCON1 = 0x0F; // chon digital
    led_io = XUAT;
    ramidx = 0;
    romidx = 0;
    dem500ms = SODEM500MS;
}

void main()
{
    init();
    timer0_init();
    while(1);
}