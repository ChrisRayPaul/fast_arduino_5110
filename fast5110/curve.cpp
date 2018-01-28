// 
// 
// 
#include "canvas.h"
#include "curve.h"

#define BUF_SZ 42
int curve[BUF_SZ] = { 0 };
float zoom_ratio = 1.0;
int dmax, dmin;
void add_data(int n)
{
	dmax = n, dmin = n;
	for (int i = 0; i < BUF_SZ - 1; i++)
	{
		curve[i] = curve[i + 1];
		if (curve[i] < dmin)
		{
			dmin = curve[i];
		}
		if (curve[i] > dmax)
		{
			dmax = curve[i];
		}
	}
	curve[BUF_SZ - 1] = n;
	if (dmax == dmin)
	{
		zoom_ratio = 0.05;
	}
	else
	{
		zoom_ratio = 48 / (dmax - dmin);
	}
}
int get_curve_y(int n)
{
	return n / 22;
}
void draw()
{
	for (int i = 0; i < BUF_SZ - 1; i++)
	{
		line(i * 84 / BUF_SZ, 47 - get_curve_y(curve[i]), (1 + i) * 84 / BUF_SZ, 47 - get_curve_y(curve[i + 1]));
	}
	lcd_putnum(dmax, 0, 0);
	lcd_putnum(dmin, 0, 5);
}