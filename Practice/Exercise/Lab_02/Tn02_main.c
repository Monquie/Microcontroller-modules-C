#include<xc.h>
#pragma config OSC=HS, WDT=OFF, LVP = OFF
#define _XTAL_FREQ 10000000

volatile unsigned char led __at(0xF8c); //LATD
volatile unsigned char led_io __at(0xF95); //TRISD
#define	NHAP	1
#define	XUAT	0
#define	__delay_ms(x) __delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
unsigned char dir; // direction of the Led motion
void init()
{
    ADCON1 = 0x0F; //dung Digital
    led_io = XUAT;
    TRISAbits.RA5=NHAP; //bit 5 cong A nhap (nut RA5)
	dir = 0;
}

void lamtre()
{
	unsigned char dem;
	for(dem=0;dem<250;dem++) __delay_ms(2);
}
void quayphai()
{
	unsigned char tam, bit7led;
	tam 	= 	led;
	bit7led = 	tam & 0x01;
	tam 	>>= 1;
	if ((bit7led)!=0) tam	|=	0x80;
	led 	=	tam;
}
void quaytrai()
{
	unsigned char tam, bit7led;
	tam 	= 	led;
	bit7led = 	tam & 0x80;
	tam 	<<= 1;
	if ((bit7led)!=0) tam	|=	0x01;
	led 	=	tam;
}
void xuly()
{
	if(PORTAbits.RA5==0)
    {
		++dir %= 2;
		while(PORTAbits.RA5==0);
    }
	if(dir == 0) {led = 0x01; lamtre(); quaytrai();}
	else {led = 0x80; lamtre(); quayphai();}
}
void main()
{
    init();
    while(1)
    {
		xuly();
    }
}