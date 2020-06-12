#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
volatile unsigned char row __at(0xF8A); //LATB
volatile unsigned char row_io __at(0xF93); //TRISB
volatile unsigned char gcol __at(0xF8B); //LATC
volatile unsigned char gcol_io __at(0xF94); //TRISC
volatile unsigned char rcol __at(0xF8C); //LATD
volatile unsigned char rcol_io __at(0xF95); //TRISD
#define XUAT        0
#define NHAP        1
#define NUTNHAN     PORTAbits.RA5
#define NUTNHAN_IO  TRISAbits.RA5
#define G_DATA      0x3C
#define R_DATA      0xCC

void init()
{
    ADCON1 = 0x0F;      //Nut nhan RA5 nhap
    NUTNHAN_IO = NHAP;  //Cac port led xuat
    row_io  =   XUAT;
    gcol_io =   XUAT;
    rcol_io =   XUAT;
}
void main(void)
{
    init();
    //row = 0; 
    gcol = G_DATA;
    rcol = R_DATA;
    row = 0b00000001;
    while(1)
    {
        if(NUTNHAN == 0)
        {
            row<<=1;
            if(row==0) {row =1;}
            while(NUTNHAN == 0);
        }
    }
}