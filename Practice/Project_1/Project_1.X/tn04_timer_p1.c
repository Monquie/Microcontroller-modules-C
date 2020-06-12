#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include "Timer.h"
volatile unsigned char led __at(0xF8C); //LATD
volatile unsigned char led_io __at(0xF95); //TRISD
#define XUAT 0
#define NHAP 1
#define SODEM500MS 50
unsigned char dem500ms;

void timer_process()
{
    if((--dem500ms)==0)
    {
        led++;
        dem500ms = SODEM500MS;
    }
}
void init()
{
    ADCON1 = 0x0F;
    led_io = XUAT;
    led = 0x00;
    dem500ms = SODEM500MS;
}
void main()
{
    init();
    timer0_init();
    while(1);
}
