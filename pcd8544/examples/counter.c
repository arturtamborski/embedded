/*** counter.c
 * This code requires the PCD8544_BUFFERED flag to be enabled
 * for clear_chars() functions.
 */


#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "util/util.h"
#include "pcd8544/pcd8544.h"


int
main(void)
{
	int8_t a = 42;
	uint8_t b = 42;

	pcd8544_init();

	pcd8544_set_pos(4, 0);
	pcd8544_puts("counter");

	while (1)
	{
		pcd8544_set_pos(4, 2);
		pcd8544_puts("a: ");
		pcd8544_clear_chars(4);
		pcd8544_puti(a);

		pcd8544_set_pos(4, 3);
		pcd8544_puts("b: ");
		pcd8544_clear_chars(3);
		pcd8544_putu(b);

		a += 1;
		b += 1;

		_delay_ms(150);
		pcd8544_draw();
	}

	return (0);
}
