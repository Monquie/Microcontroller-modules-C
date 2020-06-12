#include<xc.h>
#include<stdio.h>
#include"Usart.h"
#include"tn07_LCD.h"
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#define _XTAL_FREQ 10000000
#define XUAT        0
#define NHAP        1
#define HANG_NH     1
char kytu_tr,kytu_nh,cot_tr,cot_nh;
volatile unsigned char led __at(0xF8c);     //LATD
volatile unsigned char led_io __at(0xF95);  //TRISD

void init()
{
    lcd_init();
    TRISAbits.RA5 = NHAP;
    led_io  =   XUAT;
    led     =   0x00;
    kytu_tr =   'H';
}
void Usart_process()
{
    kytu_nh = RCREG1;
    lcd_gotoxy(HANG_NH,cot_nh);
    putchar(kytu_nh);
    if((++cot_nh)==16)  cot_nh  =   0;
}
void Rcerr_process()
{
    RCSTA1bits.CREN =   0;
    RCSTA1bits.CREN =   1;
    led =   0xFF;
}
void main()
{
    init();
    Usart_init();
    while(1){
        if(PORTAbits.RA5==0){
            Send_char(kytu_tr);
            while(PORTAbits.RA5==0);
        }
    }
}