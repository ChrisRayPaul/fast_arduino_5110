// 
// 
// 

#include "joystick.h"
static u8 _key_buf[4];
void(*_callback)(u8 code);
void joystick_bind(void(*f)(u8 code))
{
	_callback = f;
}
void joystick_scan()
{
	if (analogRead(A1) < 10)
	{
		if (_key_buf[Y_DOWN] < 100)
		{
			_key_buf[Y_DOWN]++;
			if (_key_buf[Y_DOWN] == 2)
			{
				if (NULL != _callback)
				{
					_callback(Y_DOWN);
				}
			}
		}
	}
	else
	{
		_key_buf[Y_DOWN] = 0;
	}
	if (analogRead(A1) >700)
	{
		if (_key_buf[Y_UP] < 100)
		{
			_key_buf[Y_UP]++;
			if (_key_buf[Y_UP] == 2)
			{
				if (NULL != _callback)
				{
					_callback(Y_UP);
				}
			}
		}
	}
	else
	{
		_key_buf[Y_UP] = 0;
	}
}
