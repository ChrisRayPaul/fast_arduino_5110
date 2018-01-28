// listbox.h

#ifndef _LISTBOX_h
#define _LISTBOX_h

#include "public.h"

#define MAX_ITEM_LEN 8
struct ListBox
{
	char (*data)[MAX_ITEM_LEN];
	u8 selected_index;
	u_t len;
	u_t x, y;
};

struct ListBox * listbox_create(char (*data)[MAX_ITEM_LEN],u_t len, u_t x, u_t y);
void listbox_draw(struct ListBox *);
#endif

