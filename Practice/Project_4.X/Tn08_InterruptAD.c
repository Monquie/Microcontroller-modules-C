

#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include<stdio.h>
//#include"Timer.h"
#include"tn08_LCD.h"

#define XUAT        0
#define NHAP        1
#define TINHIEU     PORTAbits.RA0
#define TINHIEU_IO  TRISAbits.RA0
#define AD_CFG0     0b00000001 // Kenh AN0, GO/nDONE = 0, ADON =1
#define AD_CFG1     0x0E       // Su dung kenh AN0
#define AD_CFG2     0b10000001 // right justified, ACQT = 0TAD, FOSC/8
unsigned char adres; // AD result

void Adc_init()
{
    TINHIEU_IO  =   NHAP;       // AN0 nhap
    ADCON0      =   AD_CFG0;    // enable ADC
    ADCON1      =   AD_CFG1;    // Chon nut nhan
    ADCON2      =   AD_CFG2;    // ... ??
    TRISAbits.RA5 = NHAP;
    RCONbits.IPEN = 1;          // khoi dong uu tien ngat
    IPR1bits.ADIP = 0;          // ngat AD uu tien thap
    PIR1bits.ADIF = 0;          // Xoa co ngat
    PIE1bits.ADIE = 1;          // cho phep ngat
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
    ADCON0bits.GO   = 1;        // Bat dau AD luon
}
void Adc_process()
{
    lcd_gotoxy(0,0);
    printf("AD CONVERSION");
    lcd_gotoxy(1,0);
    printf("%d",adres);
}

void __interrupt(low_priority) Adc_isr()
{
    if((PIE1bits.ADIE)&&(PIR1bits.ADIF))
    {
        PIR1bits.ADIF = 0;
        adres         = ADRESH*256  +   ADRESL;
        Adc_process();
        ADCON0bits.GO = 1;
    }
}
void main()
{
    lcd_init();
    Adc_init();
    while(1);
}
