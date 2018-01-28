// 
// 
// 
#include "font.h"
#define RST 2
#define CE 3
#define DC 4
#define DIN 5
#define CLK 6

#define DATA  1
#define CMD   0

static unsigned char buf[504] = { 0 };
void write_byte(byte b, byte cmd_type)
{
	int i = 0;
	PORTD &= ~(1 << CE);
	if (cmd_type == 0)
	{
		PORTD &= ~(1 << DC);
	}
	else
	{
		PORTD |= 1 << DC;
	}
	for (i = 0; i < 8; i++)
	{
		PORTD &= ~(1 << CLK);
		if ((b & (1 << (7 - i))) == 0)
		{
			PORTD &= ~(1 << DIN);
		}
		else
		{
			PORTD |= 1 << DIN;
		}
		PORTD |= 1 << CLK;
	}
	PORTD |= 1 << CE;
}

void pixel(int x, int y)
{
	if (x < 0 || x > 83 || y < 0 || y > 47)
	{
		return;
	}
	buf[(y >> 3) * 84 + x] |= 1 << (y & 0x07);
}
void box(int x, int y, int w, int h)
{
	for (int i = -w / 2; i < w / 2; i++)
	{
		for (int j = -h / 2; j < h / 2; j++)
		{
			pixel(x + i, y + j);
		}
	}
}
void rect(int x, int y, int w, int h)
{
	for (int i = -w / 2; i < w / 2; i++)
	{
		pixel(x + i, y - h / 2);
		pixel(x + i, y + h / 2);
	}
	for (int j = -h / 2; j < h / 2; j++)
	{
		pixel(x - w / 2, y + j);
		pixel(x + w / 2, y + j);
	}
}
void line(int x1, int y1, int x2, int y2)
{
	int tmp;
	int x, y;
	int dx, dy;
	int err;
	int ystep;
	uint8_t swapxy = 0;

	if (x1 > x2) dx = x1 - x2; else dx = x2 - x1;
	if (y1 > y2) dy = y1 - y2; else dy = y2 - y1;

	if (dy > dx)
	{
		swapxy = 1;
		tmp = dx; dx = dy; dy = tmp;
		tmp = x1; x1 = y1; y1 = tmp;
		tmp = x2; x2 = y2; y2 = tmp;
	}
	if (x1 > x2)
	{
		tmp = x1; x1 = x2; x2 = tmp;
		tmp = y1; y1 = y2; y2 = tmp;
	}
	err = dx >> 1;
	if (y2 > y1) ystep = 1; else ystep = -1;
	y = y1;
	for (x = x1; x <= x2; x++)
	{
		if (swapxy == 0)
			pixel(x, y);
		else
			pixel(y, x);
		err -= (uint8_t)dy;
		if (err < 0)
		{
			y += (int)ystep;
			err += (int)dx;
		}
	}
}
void lcd_putchar(char c, int x, int y)
{
	if (x < 0 || y < 0 || x >= 84 || y >= 6)
	{
		return;
	}
	const byte *p = &font5x8[(c - ' ') * 5];
	for (int i = x; (i < x + 5) && i < 84; i++)
	{
		buf[y * 84 + i] = *p;
		p++;
	}
}
void lcd_putstr(char* str, int x, int y)
{
	int offset = 0;
	while (*str)
	{
		lcd_putchar(*str, x + offset, y);
		offset += 6;
		str++;
	}
}
void lcd_putnum(int n, int x, int y)
{
	char buf[10];
	sprintf(buf, "%d", n);
	lcd_putstr(buf, x, y);
}
void lcd_show()
{
	int i;
	write_byte(0x40, CMD);
	write_byte(0x80, CMD);
	for (i = 0; i < 6 * 84; i++)
	{
		write_byte(buf[i], DATA);
	}
}
void lcd_clear()
{
	memset(buf, 0, 504);
	lcd_show();
}
void lcd_buffer_clear()
{
	memset(buf, 0, 504);
}

void nokia5110_init()
{
	pinMode(RST, OUTPUT);
	digitalWrite(RST, LOW);
	digitalWrite(RST, HIGH);
	DDRD = 0xFF;
	write_byte(0x21, CMD);
	write_byte(0x14, CMD);//bias
	write_byte(0xBA, CMD);//Vop
	write_byte(0x20, CMD);
	write_byte(0x0c, CMD);
	lcd_clear();
}