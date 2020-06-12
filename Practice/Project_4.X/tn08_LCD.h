// File lcd.h
#ifndef     LCD_H
#define     LCD_H
extern void lcd_init();
extern void lcd_putc(char);
extern void lcd_puts(const char*);
extern void lcd_cls();
extern void lcd_gotoxy(unsigned char,unsigned char);
extern void lcd_download(unsigned char,unsigned char []);
#endif
