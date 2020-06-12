
#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include "Timer1.h"
volatile unsigned char led __at(0xF8C); //LATD
volatile unsigned char led_io __at(0xF95); //TRISD
#define XUAT 0
#define NHAP 1
#define DEM1MS 1
unsigned char dem1ms;


void timer_process()
{
    if(dem1ms>0) dem1ms--;
} 
void tre1ms()
{
dem1ms=DEM1MS;
while(dem1ms>0);
}

void init()
{
    ADCON1 = 0x0F;
    led_io = XUAT;
    led = 0x00;
    dem1s = DEM1MS;
}
void main()
{
    init();
    timer1_init();
    while(1)
{ 
        
        led = 0x80 ;
        tre1ms() ;
        tre1ms() ;
        tre1ms() ;
        led = 0x00 ;
        tre1ms() ;
        tre1ms() ;
        tre1ms() ;
        tre1ms() ;
        tre1ms() ;
        tre1ms() ;
        tre1ms() ;
    }
}


