#include<xc.h>
#include<stdio.h>
#include"Timer.h"

#pragma config OSC=HS, WDT = OFF, LVP = OFF
#define _XTAL_FREQ 10000000
#define XUAT        0
#define NHAP        1
#define T_OSC       0.1         // 10.000mHz => f = 0.1 (nano)s
#define PR2_VAL     159    //249         // 1536 nano(s)
#define CCPR1L_VAL  20    //120
#define DC1B1_VAL   0      //0
#define DC1B0_VAL   0      //0
#define PWM_CFG     0x0C    //0x0C
#define TMR2_CFG    0x07    //0x05
#define TMR1_CFG    0x39
#define TMR2_PRES   16       // 16
#define PWMOUT_IO   TRISCbits.RC2   //chan phat xung
#define SODEM500MS  50

unsigned char dem500ms;
unsigned char index;

void init()
{
    ADCON1  =   0x0F;
    TRISAbits.RA5 = NHAP;
    dem500ms =  SODEM500MS;
}
void pwm_init()
{
    PWMOUT_IO   =   XUAT;   //RC2 is CCP1 input
    CCP1CON     =   PWM_CFG;
    T2CON       =   TMR2_CFG;   //  prescaler = 4
    PR2         =   PR2_VAL;
    CCPR1L      =   CCPR1L_VAL;
    CCP1CONbits.DC1B1   =   DC1B1_VAL;
    CCP1CONbits.DC1B0   =   DC1B0_VAL;
}

void Up_dutyCycle()
{
    CCPR1L  +=  CCPR1L_VAL;
    index   +=  1;
    if(index    ==  7)
    {
        index   =   0;
        CCPR1L  =   CCPR1L_VAL;
    }
}

void timer_process()
{
    if((--dem500ms)==0)
    {
        Up_dutyCycle();
        dem500ms = SODEM500MS;
    }
}
void main()
{
    init();
    pwm_init();
    timer1_init();
    while(1);
}
