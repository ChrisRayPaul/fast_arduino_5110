// canvas.h

#ifndef _CANVAS_h
#define _CANVAS_h

void pixel(int x, int y);
void box(int x, int y, int w, int h);
void rect(int x, int y, int w, int h);
void line(int x1, int y1, int x2, int y2);
void lcd_putchar(char c, int x, int y);
void lcd_putstr(char* str, int x, int y);
void lcd_putnum(int n, int x, int y);
void lcd_show();
void lcd_clear();
void lcd_buffer_clear();
void nokia5110_init();
#endif

