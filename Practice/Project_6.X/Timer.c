#include<xc.h>
#include "tn09.h"
#define SODEM10MS -12500
void timer1_reset();
void timer1_init() // init thanh ghi timer0
{
    RCONbits.IPEN =1;           //cho phep dung uu tien
    IPR1bits.TMR1IP = 0;     // timer0 uu tien thap
    PIE1bits.TMR1IE = 1;      // cho phep ngat timer0
    INTCONbits.GIEH = 1;        //cho phep ngat uu tien cao
    INTCONbits.GIEL = 1;        // cho phep ngat uu tien thap
    T1CON =0x10; //0b00010000;  // dung Fosc/4,prescaler =2
    timer1_reset();
}
void timer1_reset()
{
    TMR1IF = 0;     //xoa co ngat
    TMR1ON = 0;     // ngung dem
    TMR1 = SODEM10MS; //Nap so dem
    TMR1ON = 1;      //bat dau dem, dem' xong 10ms se~ ngat'
}
void __interrupt(low_priority) timer1_isr()
{
    if(TMR1IE & TMR1IF)
    {
        timer1_reset();     // nap lai so dem
        timer_process();
    }
}
