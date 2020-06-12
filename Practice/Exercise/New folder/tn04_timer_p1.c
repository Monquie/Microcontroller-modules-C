#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include "Timer.h"
volatile unsigned char led __at(0xF8C); //LATD
volatile unsigned char led_io __at(0xF95); //TRISD
#define XUAT 0
#define NHAP 1
#define SODEM5s 500
#define XUNG     LATDbits.RD4
#define	__delay_ms(x) __delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
unsigned char dem5s;
void lamtre()
{
	unsigned char dem;
	for(dem=0;dem<1500;dem++) __delay_ms(2);
}
void timer_process()
{
    if((--dem5s)==0)
    {
        XUNG = 1;
		lamtre();
        dem5s = SODEM5S;
		XUNG = 0;
    }
}

void init()
{
    ADCON1 = 0x0F;
    led_io = XUAT;
    led = 0x00;
    dem5s = SODEM5S;
	TRISDbits.RD4 = 0;
}
void main()
{
    init();
    timer0_init();
    while(1);
}
