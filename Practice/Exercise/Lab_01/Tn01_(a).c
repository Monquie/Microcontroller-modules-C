#include<xc.h>
#pragma	config	OSC=HS, WDT=OFF, LVP=OFF
volatile unsigned char led __at(0xF8c); //LATD
char dulieu[5]={0x00,0x03,0x0C,0x30,0xC0};
unsigned char count;
void init()
{
    ADCON1 = 0x0F; //dung Digital
    TRISD = 0; // Cong D xuat 8 bit(LEDx8) , 0 la` output , 1 la input
    led = 0x00;
    TRISAbits.RA5=1; //bit 5 cong A nhap (nut RA5)
	count = 0;
}
  //LATDbits
void xuly()
{
    if(PORTAbits.RA5==0)
    {
		if(count == 0) led = 0xFF;
		else led = 0x00;
        while(PORTAbits.RA5==0);
		++count %= 2;
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