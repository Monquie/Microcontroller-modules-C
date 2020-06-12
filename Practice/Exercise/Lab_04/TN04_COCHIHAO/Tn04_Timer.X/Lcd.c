#include <xc.h>
#include <ctype.h>
#define	LCD_CS			LATA2	    //Serial latch chip select
#define	LCD_CS_TRIS		TRISA2
#define	LCD_RST			LATF6	    //Serial latch reset
#define	LCD_RST_TRIS	TRISF6
#define PUT_CGRAM_ADDR(a)  i_write((a&0b00111111)|0b01000000)
#define PUT_CGRAM_DATA(d)  d_write(d)

#define DLMAX  8
const char dhbkstr[DLMAX][8]={ //DHBK
    {0x0F,0x0F,0x0E,0x1F,0x0E,0x0F,0x0F,0x00},
    {0x1E,0x1F,0x07,0x07,0x07,0x1F,0X1E,0x00},
    {0x1C,0x1C,0x1C,0x1F,0x1F,0x1C,0x1C,0x00},
    {0x07,0x07,0x07,0x1F,0x1F,0x07,0x07,0x00},
    {0x1F,0x1C,0x1C,0x1F,0x1C,0x1F,0x1F,0x00},
    {0x18,0x1C,0x1C,0x1E,0x07,0x1F,0X1E,0x00},
    {0x1C,0x1D,0x1F,0x1F,0x1E,0x1C,0x1C,0x00},
    {0x1C,0x18,0x10,0x18,0x1C,0x0E,0X07,0x00}
};

void lcd_DHBK();
void tre_ms(unsigned int ms)
{   for(;ms>0;ms--) _delay(2500);}
void Delay()//45ms
{   tre_ms(40);}
void LCDBusy()
{   tre_ms(2);}
void SPI_init()
{
	TRISC5=0;TRISC3=0;
	SSP1CON1=0x20;
	CKE1=1; SSP1IF=0;
}
void SPI_send(unsigned char c)
{   SSP1BUF=c;
    while(SSP1IF==0);
	SSP1IF=0;
	c=SSP1BUF;//doc bo qua    
}
void SPIportA_init()
{
	LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x00); //IODIRA
	SPI_send(0x00); //all output
	LCD_CS=1;
}
void SPIportB_init()
{
	LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x01); //IODIRB
	SPI_send(0x00); //all output
	LCD_CS=1;    
}
void Write_PortB(unsigned char d)
{
	LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x13); //GPIOB
	SPI_send(d); //data
	LCD_CS=1;
}
void Write_PortA(unsigned char mask)
{
    LCD_CS=0;
	SPI_send(0x40); //write command
	SPI_send(0x12); //GPIOA
	SPI_send(mask); //data
	LCD_CS=1;
}
void i_write(unsigned char d)
{   Write_PortA(0b00000000);
	Write_PortB(d);
	Write_PortA(0b01000000);	
	Write_PortA(0b00000000);
    LCDBusy();
}
void d_write(unsigned char d)
{	Write_PortA(0b10000000);
	Write_PortB(d);
	Write_PortA(0b11000000);
	Write_PortA(0b00000000);
    LCDBusy();
}
void lcd_put_byte(unsigned char rs, unsigned char b)
{   if (rs) d_write(b); else i_write(b);}	
void lcd_gotoxy(unsigned char row, unsigned char col)
{
    if(row!=0) col+=0x40;
	i_write(0x80|col);
}
void lcd_download(char addr,char data[])
{   unsigned char j;
    PUT_CGRAM_ADDR(addr*8);
    for(j=0;j<8;j++)
        PUT_CGRAM_DATA(data[j]);
}
void lcd_init()
{
	LCD_CS_TRIS=0;LCD_CS=1;
	LCD_RST_TRIS=0;
	LCD_RST=0; _delay(4); LCD_RST=1;  //Reset Serial latch
	SPI_init(); SPIportA_init(); SPIportB_init();
	tre_ms(100);    // delay for power on
	i_write(0b00111000); //Function Set:DL8,2 lines, 5x8 matrix
	i_write(0b00001100); //Display on, cursor off, blink off
	i_write(0b00000110); //Entry mode: increment, display not shift
    i_write(0b00000001); //Display clear
    tre_ms(1000);
    lcd_DHBK();
}
void lcd_cls()
{   i_write(0b00000001);}
void lcd_putc(char c){
	switch(c){
		case '\f':
			i_write(0b00000001); break;
		case '\n':
			lcd_gotoxy(1,0); break;
		default:
			d_write(c);
	}
}
void lcd_puts(const char* s)
{	while(*s) lcd_putc(*s++);}
void putch(unsigned char c)
{   lcd_putc(c);}
void lcd_DHBK()
{   unsigned char i;
    for(i=0;i<DLMAX;i++) 
       lcd_download(i,dhbkstr[i]);
    for(i=0;i<DLMAX;i++)
    {   //lcd_gotoxy(0,(i/2)*3+(i%2));putchar(i);
        lcd_gotoxy(1,1+i);putch(i);       
    }
}

