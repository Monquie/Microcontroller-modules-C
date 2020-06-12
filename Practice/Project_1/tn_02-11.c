#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#define _XTAL_FREQ 10000000 // gan tan so 10MHz
// Che do dao dong High Speed, tan so = 10MHz
volatile unsigned char led __at(0xF8c);
volatile unsigned char led_io __at(0xF95);
unsigned char side=0;
void init()
{
    ADCON1 = 0x0F;
    led_io = 0;
    led = 0x01;
    TRISAbits.RA5=1;
}

void quaytrai()
{
    unsigned char tam,bit7led;
    tam = led;
    bit7led = tam & 0x80;
    tam = tam<<1;
    if((bit7led)!=0)
    {
        tam = tam|1;
    }
    led = tam;
}
void quayphai()
{
    unsigned char tam,bit7led;
    tam = led;
    bit7led = tam & 0x01;
    tam = tam>>1;
    if((bit7led)!=0)
    {
        tam = tam|0x80;
    }
    led = tam;
}
void lamtre()
{
    unsigned char dem;
    for(dem=0;dem<100;dem++) __delay_ms(2);
}
void main()
{
    init();
    while(1)
    {
        lamtre();
        if(side ==1) quaytrai();
        else quayphai();
        if(PORTAbits.RA5==0){
            side ^=1;
            while(PORTAbits.RA5==0);
        }
    }
}