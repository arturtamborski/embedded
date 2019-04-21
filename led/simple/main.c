#include <avr/io.h>
#include <util/delay.h>

int
main(void)
{
	DDRC |= 0xff;
	PORTC |= 0xff;

	while (1)
	{
		_delay_ms(1000);
		PORTC ^= 0xff;
	}
}
