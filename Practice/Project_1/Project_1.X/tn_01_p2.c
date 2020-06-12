#include<xc.h
#pragma config OSC=HS, WDT = OFF, LVP = OFF
// Che do dao dong High Speed, tan so = 10MHz
volatile unsigned char led @ 0xF8c; //LATD

void init()
{
    ADCON1 = 0x0F; //Khong dung Analog
    TRISD = 0; // Cong D xuat 8 bit(LEDx8)
    led =0x00;
    TRISAbits.RA5=1; //bit 5 cong A nhap (nut RA5)
}
void xuly()
{
    unsigned char tam;
    if(PORTAbits.RA5==0)
    {
        led++;
        while(PORTAbits.RA5==0);
    }
}
void main()
{
    init();
    while(1)
    {
        xuly();
    }
}
