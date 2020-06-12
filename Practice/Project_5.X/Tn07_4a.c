#include <xc.h>
#include <ctype.h>

#define TX1_IO  TRISCbits.RC6
#define RX1_IO  TRISCbits.RC7
#define TX1_CFG 0b00100100  //TXEN=1,BRGH=1
#define RC1_CFG 0b10010000  //SPEN=1,CREN=1
#define BAUDRATE    0b01011000
#define SPBRG       2082 // 2400~1040
#define RCERROR 0b00000110
#define XUAT    0;
#define NHAP    1;
void Usart_process();
void Rcerr_process();
void Usart_init()
{
    TXSTA1  =   TX1_CFG;    //chon TXSTA1
    SPBRG1  =   BAUDRATE;
    RCSTA1  =   RC1_CFG;    //chon RCSTA1
    RCONbits.IPEN   =   1;
    IPR1bits.RC1IP  =   0;  //ngat nhan ky tu uu tien thap
    PIR1bits.RC1IF  =   0;  //xoa co ngat nha.n
    PIE1bits.RC1IE  =   1;  //cho phep dung` ngat' nha.n
    INTCONbits.GIEH =   1;  //cho phep ngat toan cuc
    INTCONbits.GIEL =   1;
    TX1_IO  =   XUAT;
    RX1_IO  =   NHAP;
}

void __interrupt(low_priority) Usart_isr()
{
    if((PIR1bits.RC1IF == 1)&& (PIE1bits.RC1IE == 1))
    {
        if((RCSTA1 & RCERROR) ==  0)
            Usart_process();
        else
            Rcerr_process();
    }
}
void Send_char(char c)
{
    TXREG1  =   c;              // dem. du lieu truyen/nhan
    while(PIR1bits.TX1IF == 0);
}

