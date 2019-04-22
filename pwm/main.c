#include <avr/io.h>
#include <util/delay.h>

int
main(void)
{
	DDRC  |= 0xFF;
	PORTC |= 0xFF;

	PORTC = 0xFF;
	_delay_ms(8);
	PORTC = 0x00;
	_delay_ms(8);

	uint16_t i = 0;

	while (1)
	{
		PORTC = 0xFF;
		_delay_ms(2);
		PORTC = 0x00;
		_delay_ms(18);
	}
}
