#include<xc.h>
#pragma config OSC=HS, WDT = OFF, LVP = OFF
#include<stdio.h>
#include"Timer.h"
#include"tn08_LCD.h"

#define SODEM3S     300
#define XUAT        0
#define NHAP        1

#define ADC_IO      TRISFbits.RF0
#define ADC_NHAN    PORTFbits.RF0

#define AD_CFG0     0b00010101 // Kenh AN5, GO/nDONE = 0, ADON =1
#define AD_CFG1     0x05       // Su dung kenh AN5
#define AD_CFG2     0b00000100 // left justified, ACQT = 0TAD, FOSC/4
unsigned char adres;           // AD result
unsigned char dem3s;

void Adc_init()
{
    TINHIEU_IO  =   NHAP;
    ADC_IO      =   NHAP;
    ADCON0      =   AD_CFG0;
    ADCON1      =   AD_CFG1;
    ADCON2      =   AD_CFG2;
    dem3s       =   SODEM3S;
    
    RCONbits.IPEN = 1;          // khoi dong uu tien ngat
    IPR1bits.ADIP = 0;          // ngat AD uu tien thap
    PIR1bits.ADIF = 0;          // Xoa co ngat
    PIE1bits.ADIE = 1;          // cho phep ngat
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
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
        adres         = ADRESH*4  +   ADRESL;
        Adc_process();
    }
}
void timer_process()
{
    if((--dem3s==0))
    {
        ADCON0bits.GO   =   1;
        dem3s   =   SODEM3S;
    }
}

void main()
{
    lcd_init();
	Adc_init();
    timer0_init();
    while(1);
}
