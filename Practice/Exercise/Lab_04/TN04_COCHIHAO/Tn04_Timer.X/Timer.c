#include<xc.h>
#include "tn04.h"
#define SODEM10MS -12500
void timer0_reset();
void timer1_reset() ;
void timer0_init()
{
    RCONbits.IPEN =1;           //cho phep dung uu tien
    INTCON2bits.TMR0IP = 0;     // timer0 uu tien thap
    INTCONbits.TMR0IE = 1;      // cho phep ngat timer0
    INTCONbits.GIEH = 1;        //cho phep ngat uu tien cao
    INTCONbits.GIEL = 1;        // cho phep ngat uu tien thap
    T0CON =0;                   // dung Fosc/4,prescaler =2
    timer0_reset();
}
void timer0_reset()
{
    TMR0IF = 0;     //xoa co ngat
    TMR0ON = 0;     // ngung dem
    TMR0 = SODEM10MS; //Nap so dem
    TMR0ON = 1;      //bat dau dem
} 
/*void __interrupt(low_priority) timer0_isr()
{
    if(TMR0IE & TMR0IF)
    {
        timer0_reset();     // nap lai so dem
        timer_process();
    }
} */

void timer1_init()
{
    RCONbits.IPEN =1;           //cho phep dung uu tien
    IPR1bits.TMR1IP = 0;     // timer1 uu tien thap
    PIE1bits.TMR1IE = 1;      // cho phep ngat timer1
    INTCONbits.GIEH = 1;        //cho phep ngat uu tien cao
    INTCONbits.GIEL = 1;        // cho phep ngat uu tien thap
    T1CON =0x10;                   // dung Fosc/4,prescaler =2
    timer1_reset();
}
void timer1_reset()
{
    PIR1bits.TMR1IF = 0;         //xoa co ngat
    T1CONbits.TMR1ON = 0;        // ngung dem
    TMR1 = SODEM10MS;           //Nap so dem
    T1CONbits.TMR1ON = 1;       //bat dau dem
}
void __interrupt(low_priority) timer1_isr()
{
    if(TMR1IE & TMR1IF)
    {
        timer1_reset();     // nap lai so dem
        timer_process();
    }
}


