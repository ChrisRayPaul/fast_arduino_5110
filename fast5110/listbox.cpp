// 
// 
// 

#include "listbox.h"
#include "canvas.h"
struct ListBox * listbox_create(char (*data)[MAX_ITEM_LEN], u_t len,u_t x, u_t y)
{
	struct ListBox *lb =(struct ListBox*) malloc(sizeof(struct ListBox));
	lb->data = data;
	lb->x = x;
	lb->y = y;
	lb->len = len;
	return lb;
}
static void listbox_up()
{
	
}
static void listbox_down()
{

}
void listbox_draw(struct ListBox *lb)
{
	line(lb->x, lb->y * 8 -2, lb->x + MAX_ITEM_LEN * 6, lb->y*8-2);
	line(lb->x, lb->y * 8 - 2, lb->x + MAX_ITEM_LEN * 6/2, lb->y * 8 - 5);
	line(lb->x + MAX_ITEM_LEN * 6 / 2, lb->y * 8 - 5, lb->x + MAX_ITEM_LEN * 6, lb->y * 8 - 2);
	lcd_putstr(lb->data[lb->selected_index], lb->x+(MAX_ITEM_LEN-strlen(lb->data[lb->selected_index]))*6/2, lb->y);
	line(lb->x, lb->y * 8 +9, lb->x + MAX_ITEM_LEN * 6, lb->y * 8 + 9);
	line(lb->x, lb->y * 8 + 9, lb->x + MAX_ITEM_LEN * 6 / 2, lb->y * 8 + 13);
	line(lb->x + MAX_ITEM_LEN * 6 / 2, lb->y * 8 + 13, lb->x + MAX_ITEM_LEN * 6, lb->y * 8 + 9);
}
