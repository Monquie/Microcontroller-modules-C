#include<xc.h>
#include<stdio.h>
#include "tn04_Lcd.h"
#include "Timer.h"
#pragma config OSC=HS, WDT=OFF, LVP=OFF
#define N       20
#define SODEM500MS 50
unsigned char dem500ms;
unsigned char display_num;
unsigned char row,col;

void init()
{
    ADCON1=0x0F; // Nhap digital
    display_num = 0;
    dem500ms = SODEM500MS;
}

void timer_process()
{
    if((--dem500ms)==0)
    {
        lcd_gotoxy(row,col);
        printf("\f%d!=\n%e",N,display_num);
        display_num++;
        if(col<15){col++;}
        else{row++;row%=2;}
        dem500ms = SODEM500MS;
    }
}

void main()
{
    float x;
    init();
    lcd_init();
    timer0_init();
    while(1);
}
