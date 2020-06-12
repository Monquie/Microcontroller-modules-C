#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#define _XTAL_FREQ 10000000
// Dinh nghia du lieu ROM
#define MAXIDX1 8
#define	MAXIDX2	16
const unsigned char dl_rom1[MAXIDX1]={0x00,0x81,0xC3,0xE7,0xFF,0xE7,0xC3,0x81};
const unsigned char dl_rom2[MAXIDX2]={0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,
									  0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01};
#define XUAT 0
#define NHAP 1
#define	__delay_ms(x) __delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
unsigned char dl_ram1[MAXIDX1],dl_ram2[MAXIDX2],ramidx,ql;
volatile unsigned char led __at(0xF8c);
volatile unsigned char led_io __at(0xF95);
void doi_ql()
{
	if(ql == 0)
	{
		for(unsigned char i=0;i<MAXIDX1;i++){
			dl_ram1[i]=dl_rom1[i];
		}
	}
	else
	{
		for(unsigned char i=0;i<MAXIDX2;i++){
			dl_ram2[i]=dl_rom2[i];
		}
	}
}
void xuatled()
{
    led = dl_ram[ramidx++];
	if(ql == 0){ramidx%=MAXIDX1;}
    else {ramidx%=MAXIDX2;}
}
void init()
{
    ADCON1 = 0x0F; //chon digital
    led_io = XUAT; //port lED xuat
    TRISBbits.RB0 = NHAP;
	ql = 0;
    ramidx = 0;
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
	++ql %= 2;
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