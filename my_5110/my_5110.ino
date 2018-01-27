#include "canvas.h"
#define sin_pin 9
#define quad_pin 10
void setup() {
  // put your setup code here, to run once:
  nokia5110_init();
  pinMode(sin_pin,OUTPUT);
  pinMode(quad_pin,OUTPUT);
}
float x = 10;
float t = 10.0;
#define BUF_SZ 42
int curve[BUF_SZ] = {0};
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
  return n/22;
}
void draw()
{
  for (int i = 0; i < BUF_SZ - 1; i++)
  {
    line(i * 84 / BUF_SZ, 47-get_curve_y(curve[i]), (1 + i) * 84 / BUF_SZ, 47-get_curve_y(curve[i + 1]));
  }
  lcd_putnum(dmax,0,0);
  lcd_putnum(dmin,0,5);
}
int fps = 30;
long start_tick = 0;
void loop() {
  // put your main code here, to run repeatedly:
  start_tick = millis();
  lcd_buffer_clear();
  if(int(x)%5==0)
  {
    add_data(analogRead(A0));
  }
  draw();
  lcd_show();
  x += 0.5;
  analogWrite(quad_pin,sin(x/30.0)*200+300);
  //digitalWrite(quad_pin,(int(x)%4)>=2);
  while (millis() - start_tick < (1000 / fps))
  {
    ;
  }
}









