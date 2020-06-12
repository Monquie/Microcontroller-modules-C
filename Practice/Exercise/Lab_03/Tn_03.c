#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
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
#define	__delay_ms(x) __delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
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
void init()
{
    ADCON1 = 0x0F; //chon digital
    led_io = XUAT; //port lED xuat
    TRISBbits.RB0 = NHAP;
    ramidx = 0;
    romidx = 0;
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
    doi_ql();
    xuatled();
}
void lamtre()
{
    unsigned char dem;
    for(dem=0;dem<250;dem++) __delay_ms(2);
}
void main()
{
    init();
    int0_init();
    while(1){
        xuatled();
        lamtre();
    }
}