#include <avr/io.h>
#include <util/setbaud.h>

#include "uart.h"

void
uart_init(void)
{
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	
#if USE_2X
	UCSRA |= (1 << U2X);
#else
	UCSRA &= ~(1 << U2X);
#endif
}

void
uart_putrn(void)
{
	uart_putc('\r');
	uart_putc('\n');
}

void
uart_putc(char c)
{
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
}

void
uart_puts(char *s)
{
	while (*s)
		uart_putc(*s++);
}

char
uart_getc(void)
{
	loop_until_bit_is_set(UCSRA, RXC);
	return UDR;
}
