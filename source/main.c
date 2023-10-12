#include <main.h>

extern void do_led_off(u32_t);

void do_system_initial(void)
{
	malloc_init();

	s5pv210_clk_initial();
	s5pv210_irq_initial();
	s5pv210_tick_initial();
	s5pv210_tick_delay_initial();

	s5pv210_serial_initial();
	s5pv210_fb_initial();

	led_initial();
	beep_initial();
	key_initial();
}

int main(int argc, char * argv[])
{
	int i;
	for(i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			asm("swi 0x0"); // create an SWI interrupt
			mdelay(500);	// delay 500ms
			do_led_off(0);	// turn off the LED
			break;
		case 1:
			asm("swi 0x1"); 
			mdelay(500);
			do_led_off(1);
			break;
		case 2:
			asm("swi 0x2"); 
			mdelay(500);
			do_led_off(2);
			break;
		case 3:
			asm("swi 0x3"); 
			mdelay(500);
			do_led_off(3);
			break;
		default:
			break;
		}
		if(i == 3)
			i = -1;
	} 

	return 0;
}
