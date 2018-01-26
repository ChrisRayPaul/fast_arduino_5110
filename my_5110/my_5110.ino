
#define RST 2
#define CE 3
#define DC 4
#define DIN 5
#define CLK 6

#define DATA  1
#define CMD   0
unsigned char buf[504] = {0};


void write_byte(byte b, byte cmd_type)
{
  int i = 0;
  PORTD &= ~(1<<CE);
  if(cmd_type==0)
  {
    PORTD &=~(1<<DC);
  }
  else
  {
    PORTD |=1<<DC;
  }
  for (i = 0; i < 8; i++)
  {
    PORTD &=~(1<<CLK);
    if((b & (1 << (7 - i))) == 0)
    {
      PORTD &=~(1<<DIN);
    }
    else
    {
      PORTD |=1<<DIN;
    }
    PORTD |=1<<CLK;
  }
  PORTD |= 1<<CE;
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
  memset(buf,0,504);
  lcd_show();
}
void lcd_buffer_clear()
{
  memset(buf,0,504);
}
void nokia5110_init()
{
  pinMode(RST,OUTPUT);
  digitalWrite(RST,LOW);
  digitalWrite(RST,HIGH);
  DDRD=0xFF;
  write_byte(0x21, CMD);
  write_byte(0x14, CMD);//bias
  write_byte(0xBA, CMD);//Vop
  write_byte(0x20, CMD);
  write_byte(0x0c, CMD);
  lcd_clear();
}
void pixel(int x,int y)
{
  if(x<0 || x>83 || y<0 ||y >47)
  {
    return;
  }
  buf[(y>>3)*84+x] |=1<<(y&0x07);
}
void setup() {
  // put your setup code here, to run once:
  nokia5110_init();
}
float x=10;
float t=10.0;
void box(int x,int y,int w,int h)
{
  for(int i=-w/2;i<w/2;i++)
  {
    for(int j=-h/2;j<h/2;j++)
    {
      pixel(x+i,y+j);
    }
  }
}
void rect(int x,int y,int w,int h)
{
  for(int i=-w/2;i<w/2;i++)
  {
    pixel(x+i,y-h/2);
    pixel(x+i,y+h/2);
  }
  for(int j=-h/2;j<h/2;j++)
  {
    pixel(x-w/2,y+j);
    pixel(x+w/2,y+j);
  }
}
void draw()
{
  for(int i=0;i<84;i++)
  {
    pixel(i,sin(i/10.0+cos(x/10.0)*20)*t+24);
    pixel(i,sin(i/10.0+cos(x/10.0)*20)*t+25);
    pixel(i-1,sin(i/10.0+cos(x/10.0)*20)*t+24);
    pixel(i-1,sin(i/10.0+cos(x/10.0)*20)*t+25);
  }
}
int fps=15;
long start_tick=0;
void loop() {
  // put your main code here, to run repeatedly:
  start_tick=millis();
  lcd_buffer_clear();
  draw();
  lcd_show();
  x+=0.1;
  t=sin(x/2.0)*10+12;
  
  while(millis()-start_tick<(1000/fps))
  {
    ;
  }
}









