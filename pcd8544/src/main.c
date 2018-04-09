#include <avr/io.h>
#include <util/delay.h>

#include "util/util.h"
#include "pcd8544/pcd8544.h"


int
main(void)
{
	uint8_t hours = 17, minutes = 15;
	uint8_t val = 0;

	DDRC |= 0xff;
	PORTC |= 0xff;

	pcd8544_init();
	pcd8544_set_xy(0, 0);
	pcd8544_puts(" PCD 8544 driver");
	pcd8544_set_pos(0, 1);
	pcd8544_puts(" library for AVR");
	pcd8544_set_pos(0, 2);
	pcd8544_puts("   written by");
	pcd8544_set_pos(0, 3);
	pcd8544_puts("Artur Tamborski");

	//for (y = 0; y < 6; y++)
	//	for (x = 0; x < PCD8544_SCREEN_WIDTH; x++)
	//		pcd8544_send_data(my_image[y*PCD8544_SCREEN_WIDTH + x]);

	while (1)
	{
		pcd8544_set_pos(0, 4);
		pcd8544_clear_line();
		pcd8544_putu(val % 8);

		//pcd8544_set_bias(val % 8);

		val++;

		PORTC ^= 0xff;
		pcd8544_draw();
		_delay_ms(1000);
	}

//	while (1)
//	{
//		pcd8544_set_pos(0, 4);
//		pcd8544_puts("time: ");
//		pcd8544_clear_line();
//		pcd8544_putu(hours);
//		pcd8544_putc(':');
//		pcd8544_putu(minutes);
//		pcd8544_set_pos(0, 5);
//		pcd8544_puts("date: Thu 15 Apr");
//
//		minutes++;
//
//		if (minutes >= 59)
//			minutes = 0, hours++;
//
//		if (hours >= 23)
//			hours = 0;
//
//		_delay_ms(500);
//		PORTC ^= 0xff;
//		pcd8544_draw();
//	}

	return (0);
}
