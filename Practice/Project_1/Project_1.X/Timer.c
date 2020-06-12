#include<xc.h>
#include "tn04.h"
#define SODEM10MS -12500
void timer0_reset();
void timer0_init() // init thanh ghi timer0
{
    RCONbits.IPEN =1;           //cho phep dung uu tien
    INTCON2bits.TMR0IP = 0;     // timer0 uu tien thap
    INTCONbits.TMR0IE = 1;      // cho phep ngat timer0
    INTCONbits.GIEH = 1;        //cho phep ngat uu tien cao
    INTCONbits.GIEL = 1;        // cho phep ngat uu tien thap
    T0CON =0b000;               // dung Fosc/4,prescaler =2
    timer0_reset();
}
void timer0_reset()
{
    TMR0IF = 0;     //xoa co ngat
    TMR0ON = 0;     // ngung dem
    TMR0 = SODEM10MS; //Nap so dem
    TMR0ON = 1;      //bat dau dem, dem' xong 10ms se~ ngat'
}
void __interrupt(low_priority) timer0_isr()
{
    if(TMR0IE & TMR0IF)
    {
        timer0_reset();     // nap lai so dem
        timer_process();
    }
}
