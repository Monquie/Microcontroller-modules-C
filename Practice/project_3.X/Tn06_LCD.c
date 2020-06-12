#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include<stdio.h>
#include"Timer.h"
#include"tn06_LCD.h"

#define XUAT        0
#define NHAP        1
#define MAXIDX      4
#define X4N4        0x0F

#define ROW0        0b11101111

volatile unsigned char keyout   __at(0xF8A);  //LATB
volatile unsigned char keyin    __at(0xF81);  //PORTB
volatile unsigned char key_io   __at(0xF93);  //TRISB

#define COL0        0b00001110
#define COL1        0b00001101
#define COL2        0b00001011
#define COL3        0b00000111
#define NOKEY       0xFF

unsigned char idx;
unsigned char keyreg;

/*-----------------------------------------------------------*/
void getkey()
{
    unsigned char col;
    col = keyin & 0x0F; // RB3-RB0
    switch (col)
    {
        case COL0: keyreg =0; break;
        case COL1: keyreg =1; break;
        case COL2: keyreg =2; break;
        case COL3: keyreg =3; break;
        default: keyreg = NOKEY;
    }
    // doi ra so thu tu (keycode)
    if(keyreg!=NOKEY) keyreg += (idx*4);
}
void xulyphim()
{
    printf("\f%d!=\n%e",keyreg);
}
void quetphim()
{
    unsigned char dl_quet;
    keyout = 0xFF; // chon hang theo idx
    dl_quet = ROW0<<idx;
    keyout = dl_quet;
    getkey(); // doc cot, phat hien phim
    idx = (++idx)%MAXIDX;
    if(keyreg!=NOKEY) xulyphim();
}
/*-----------------------------------------------------------*/

void init()
{
    ADCON1 = 0x0F;
    key_io  =   X4N4;   //B7-B4:hang xuat, B3-B0:cot nhap
}
void main()
{
    init();
    lcd_init();
    while(1){
        quetphim();
    }
}
