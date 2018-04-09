#include <stdlib.h>

#include <util/delay.h>

#include "uart/uart.h"
#include "ds18b20/ds18b20.h"


int
main(void)
{
	char buf[8];
	double temp;

	uart_init();

	while (1)
	{
		temp = ds18b20_read_temp();

		dtostrf(temp, 0, 2, buf);

		uart_puts("temp: ");
		uart_puts(buf);
		uart_puts(".C");
		uart_putrn();

		_delay_ms(500);
	}

	return (0);
}
