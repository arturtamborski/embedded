/*** main.c
 */


#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "util/util.h"
#include "pcd8544/pcd8544.h"


int
main(void)
{
	DDRC |= 0xff;
	PORTC |= 0xff;

	pcd8544_init();
	pcd8544_puts(" PCD 8544 driver");
	pcd8544_set_pos(0, 1);
	pcd8544_puts(" library for AVR");
	pcd8544_set_pos(0, 2);
	pcd8544_puts("   written by");
	pcd8544_set_pos(0, 3);
	pcd8544_puts("Artur Tamborski");
	
	pcd8544_draw();

	//for (y = 0; y < 6; y++)
	//	for (x = 0; x < PCD8544_SCREEN_WIDTH; x++)
	//		pcd8544_send_data(my_image[y*PCD8544_SCREEN_WIDTH + x]);

	while (1)
	{
		PORTC ^= 0xff;
		_delay_ms(1000);
	}

	return (0);
}
