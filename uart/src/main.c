#include <util/delay.h>

#include "uart/uart.h"


int
main(void)
{
	uint8_t cnt = 0;

	uart_init();

	while (1)
	{
		uart_putc('[');
		uart_putc((cnt % 10) + '0');
		uart_putc(']');
		uart_puts(" testing uart connection at baud rate 9600");
		uart_putrn();

		_delay_ms(500);
		cnt++;
	}

	return (0);
}
