// joystick.h

#ifndef _JOYSTICK_h
#define _JOYSTICK_h
#include "public.h"
#define Y_UP 2
#define Y_DOWN 3
void joystick_bind(void(*f)(u8 code));
void joystick_scan();

#endif

