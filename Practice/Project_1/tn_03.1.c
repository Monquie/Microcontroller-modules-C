#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#define _XTAL_FREQ 10000000
// Dinh nghia du lieu ROM
const unsigned char dl_rom[4] ={0x55,0xAA,0x3C,0xC3};
unsigned char dl_ram[4];
#define MAXIDX 4;
#define XUAT 0
#define NHAP 1
unsigned char idx;
volatile unsigned char led __at(0xF8c); //LATD
volatile unsigned char led_io __at(0xF95); //TrisD
void rom2ram()
{
    for(unsigned char i=0;i<4;i++)
    {
      dl_ram[i] = dl_rom[i];
    }
}
void xuatled()
{
    led = dl_ram[idx++];
    idx%=MAXIDX;
}
void init()
{
    ADCON1 = 0x0F; //chon digital
    led_io = XUAT; //port lED xuat
    TRISBbits.RB0 = NHAP; // nhan nut de? ngat
    idx = 0;
    xuatled();
}
void int0_init()
{
    RCONbits.IPEN = 1;          //su dung uu tien
    INTCONbits.INT0IF = 0;     // xoa co ngat
    INTCONbits.INT0IE = 1;     // cho phep ngat
    INTCONbits.GIEH = 1;       // cho phep ngat toan cuc
}
void __interrupt(high_priority) int0_isr()
{
    INTCONbits.INT0IF = 0;
    rom2ram();
    xuatled();
}
void lamtre()
{
    unsigned char dem;
    for(dem=0;dem<100;dem++) __delay_ms(2);
}
void main()
{
    init();
    int0_init();
    while(1);
}