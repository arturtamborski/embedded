#include <avr/io.h>

#include "pcd8544/pcd8544.h"

int
main(void)
{
	pcd8544_init();

	pcd8544_set_pos(4, 0);
	pcd8544_puts("simplest");

	pcd8544_set_pos(4, 1);
	pcd8544_puts("possible");

	while (1);

	return (0);
}
