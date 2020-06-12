#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include<stdio.h>
//#include"Timer.h"
#include"tn08_LCD.h"

#define XUAT        0
#define NHAP        1
#define TINHIEU     PORTAbits.RA0     //chan RA0 noi voi dien tro R3
#define TINHIEU_IO  TRISAbits.RA0
#define AD_CFG0     0b00000001 // Kenh AN0, GO/nDONE = 0, ADON =1
#define AD_CFG1     0x0E       // Su dung kenh AN0
#define AD_CFG2     0b10000001 // right justified, ACQT = 0TAD, FOSC/8
unsigned char adres; // AD result

void Adc_init()
{
    TINHIEU_IO  =   NHAP; // AN0 nhap
    ADCON0      =   AD_CFG0;
    ADCON1      =   AD_CFG1;
    ADCON2      =   AD_CFG2;
    TRISAbits.RA5 = NHAP;
}
void Adc_process()
{
    lcd_gotoxy(0,0);
    printf("AD CONVERSION");
    lcd_gotoxy(1,0);
    printf("%d",adres);
}
void Adc_update()
{
    ADCON0bits.GO   =   1;
    while(ADCON0bits.DONE); // chuyen xong
    adres          =   ADRESH*256  +   ADRESL;
    Adc_process();
}

void main()
{
    lcd_init();
    Adc_init();
    while(1){
        if(PORTAbits.RA5==0){
            Adc_update();
            while(PORTAbits.RA5==0);
        }
    }
}
