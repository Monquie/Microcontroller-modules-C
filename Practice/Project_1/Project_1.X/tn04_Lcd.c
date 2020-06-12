#include <xc.h>
#include <ctype.h>
#define	LCD_CS			LATA2	    //Serial latch chip select
#define	LCD_CS_TRIS		TRISA2
#define	LCD_RST			LATF6	    //Serial latch reset
#define	LCD_RST_TRIS	TRISF6
#define PUT_CGRAM_ADDR(a)  i_write((unsigned char)((a&0b00111111)|0b01000000))
#define PUT_CGRAM_DATA(d)  d_write(d)

#define DLMAX  8
const unsigned char dhbkstr[DLMAX][8]={ //DHBK
    {0x0F,0x0F,0x0E,0x1F,0x0E,0x0F,0x0F,0x00},
    {0x1E,0x1F,0x07,0x07,0x07,0x1F,0X1E,0x00},
    {0x1C,0x1C,0x1C,0x1F,0x1F,0x1C,0x1C,0x00},
    {0x07,0x07,0x07,0x1F,0x1F,0x07,0x07,0x00},
    {0x1F,0x1C,0x1C,0x1F,0x1C,0x1F,0x1F,0x00},
    {0x18,0x1C,0x1C,0x1E,0x07,0x1F,0X1E,0x00},
    {0x1C,0x1D,0x1F,0x1F,0x1E,0x1C,0x1C,0x00},
    {0x1C,0x18,0x10,0x18,0x1C,0x0E,0X07,0x00}
};
#define _XTAL_FREQ 10000000
void lcd_DHBK(void);
void tre_ms(unsigned int p10ms)
{   for(;p10ms>0;p10ms--) _delay(250);}
//void Delay(void)//45ms
//{   tre_ms(40);}
#pragma interrupt_level 1
void LCDBusy(void)
{   _delay(95);}
void SPI_init(void)
{
	TRISC5=0;TRISC3=0;
	SSP1CON1=0x20;
	CKE1=1; SSP1IF=0;
}
#pragma interrupt_level 1
void SPI_send(unsigned char c)
{   SSP1BUF=c;
    while(SSP1IF==0);
	SSP1IF=0;
	c=SSP1BUF;//doc bo qua    
}
void SPIportA_init(void)
{
	LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x00); //IODIRA
	SPI_send(0x00); //all output
	LCD_CS=1;
}
void SPIportB_init(void)
{
	LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x01); //IODIRB
	SPI_send(0x00); //all output
	LCD_CS=1;    
}
#pragma interrupt_level 1
void Write_PortB(unsigned char d)
{
	LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x13); //GPIOB
	SPI_send(d); //data
	LCD_CS=1;
}
#pragma interrupt_level 1
void Write_PortA(unsigned char mask)
{
    LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x12); //GPIOA
	SPI_send(mask); //data
	LCD_CS=1;
}
#pragma interrupt_level 1
void i_write(unsigned char d)
{   Write_PortA(0b00000000);
	Write_PortB(d);
	Write_PortA(0b01000000);	
	Write_PortA(0b00000000);
    LCDBusy();
}
#pragma interrupt_level 1
void d_write(unsigned char d)
{	Write_PortA(0b10000000);
	Write_PortB(d);
	Write_PortA(0b11000000);
	Write_PortA(0b00000000);
    LCDBusy();
}
void lcd_put_byte(unsigned char rs, unsigned char b)
{   if (rs) d_write(b); else i_write(b);}	
#pragma interrupt_level 1
void lcd_gotoxy(unsigned char row, unsigned char col) // LCD have 2 rows,16 cols
{
    if(row!=0) col+=0x40;
	i_write((unsigned char)(0x80|col));
}
void lcd_download(unsigned char addr,const unsigned char data[])
{   unsigned char j;
    PUT_CGRAM_ADDR(addr*8);
    for(j=0;j<8;j++)
        PUT_CGRAM_DATA(data[j]);
}
#pragma interrupt_level 1
void lcd_cls(void) // clear all the display of LCD
{   i_write(0b00000001);_delay(3708);}
void lcd_init(void) // boot (khoi dong) the LCD
{
    LCD_CS_TRIS=0;LCD_RST_TRIS=0;
    LCD_CS=1;
    LCD_RST=0; _delay(4); LCD_RST=1;  //Reset Serial latch
    SPI_init(); SPIportA_init(); SPIportB_init();

    tre_ms(60);    // delay for power on
    i_write(0b00110000);
    tre_ms(41);
    i_write(0b00110000);
    _delay(158);
    i_write(0b00110000);
    i_write(0b00111000); //Function Set:DL8,2 lines, 5x8 matrix
    i_write(0b00001100); //Display on, cursor off, blink off
    //i_write(0b00000001); //Display clear
    i_write(0b00000110); //Entry mode: increment, display not shift
    //tre_ms(10000);
    lcd_cls();
    lcd_DHBK();
}
#pragma interrupt_level 1
void lcd_putc(char c){
	switch(c){
		case '\f':
			lcd_cls(); break;
		case '\n':
			lcd_gotoxy(1,0); break;
		default:
			d_write(c);
	}
}
#pragma interrupt_level 1
void lcd_puts(const char* s) 
{	while(*s) lcd_putc(*s++);}
#pragma interrupt_level 1
void putch(unsigned char c)
{   lcd_putc(c);}
#pragma interrupt_level 1
void lcd_DHBK(void)
{   unsigned char i;
    for(i=0;i<DLMAX;i++) lcd_download(i,dhbkstr[i]);
    lcd_gotoxy(1,8);
    for(i=0;i<DLMAX;i++) putch(i);
}
