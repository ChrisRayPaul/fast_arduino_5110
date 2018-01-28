#include "joystick.h"
#include "gui.h"
void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	gui_init();
	
}
long long ticks =0;

int fps = 30;
long start_tick = 0;
void loop() {
	// put your main code here, to run repeatedly:
	start_tick = millis();
	gui_draw();
	ticks++;
	while (millis() - start_tick < (1000 / fps))
	{
		;
	}
	joystick_scan();
}
