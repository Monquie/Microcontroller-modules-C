#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
//#include"Timer.h"

#define XUAT        0
#define NHAP        1
#define X4N4    0x0F // 4 bit thap la nhap 
#define ROW0    0b11101111
#define ROW1    0b11011111
#define ROW2    0b10111111
#define ROW3    0b01111111

volatile unsigned char keyout   __at(0xF8A);  //LATB
volatile unsigned char keyin    __at(0xF81);  //PORTB
volatile unsigned char key_io   __at(0xF93);  //TRISB
volatile unsigned char led      __at(0xF8C);  //LATD
volatile unsigned char led_io   __at(0xF95);  //TRISD

void init()
{
    ADCON1  =   0x0F;   //Nhap digital
    key_io  =   X4N4;   //B7-B4:hang xuat, B3-B0:cot nhap
    led_io  =   XUAT;   //port LED xuat
    led     =   0;
}

void main(void)
{
    init();
    keyout = ROW3; // Xuat du lieu ra cong chon hang`
    while(1) led = keyin;
}
