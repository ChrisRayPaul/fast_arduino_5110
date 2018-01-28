// 
// 
// 

#include "gui.h"
#include "joystick.h"
struct ListBox * lb;

void key_event(u8 code)
{
	Serial.println(code);
	switch (code)
	{
	case Y_DOWN:
		if (lb->selected_index < lb->len-1)
		{
			lb->selected_index++;
		}
		break;
	case Y_UP:
		if (lb->selected_index > 0)
		{
			lb->selected_index--;
		}
		break;
	}
}
char items[][MAX_ITEM_LEN] = { "menu1","m2","menu3","bmmmmm4" };
void gui_init()
{
	nokia5110_init();
	joystick_bind(key_event);
	lb = listbox_create(items,sizeof(items)/sizeof(items[0]), 10, 3);
	lb->selected_index = 0;
}
void gui_draw()
{
	lcd_buffer_clear();
	lcd_putstr("Ray's Toys", 5, 0);
	listbox_draw(lb);
	lcd_show();
}
