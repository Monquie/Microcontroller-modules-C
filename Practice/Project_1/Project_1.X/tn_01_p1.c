#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#define _XTAL_FREQ 10000000 // gan tan so 10MHz = 10^7 Hz
// Che do dao dong High Speed, tan so = 10MHz
volatile unsigned char led __at(0xF8c); //LATD
char dulieu[5]={0x00,0x03,0x0C,0x30,0xC0};
int dem=0,tang=0;
void init()
{
    ADCON1 = 0x0F; //dung Digital
    TRISD = 0; // Cong D xuat 8 bit(LEDx8) , 0 la` output , 1 la input
    led =0x03;
    TRISAbits.RA5=1; //bit 5 cong A nhap (nut RA5)
}
  //LATDbits
void xuly()
{
    unsigned char tam;
    if(PORTAbits.RA5==0)
    {
        led=led<<2;
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

