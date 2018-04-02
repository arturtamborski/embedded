#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../util/util.h"
#include "ds18b20.h"

uint8_t
ds18b20_reset()
{
	uint8_t val;

	OUTPUT(DS18B20_DDR, DS18B20_BIT);
	LOW(DS18B20_PORT, DS18B20_BIT);
	_delay_us(480);

	INPUT(DS18B20_DDR, DS18B20_BIT);
	_delay_us(60);

	val = IS_HIGH(DS18B20_PIN, DS18B20_BIT);
	_delay_us(420);

	return (val);
}

void
ds18b20_write_bit(uint8_t bit)
{
	OUTPUT(DS18B20_DDR, DS18B20_BIT);
	LOW(DS18B20_PORT, DS18B20_BIT);
	_delay_us(1);

	//if we want to write 1, release the line (if not will keep low)
	if (bit)
		INPUT(DS18B20_DDR, DS18B20_BIT);

	_delay_us(60);
	INPUT(DS18B20_DDR, DS18B20_BIT);
}

uint8_t
ds18b20_read_bit(void)
{
	uint8_t bit;

	OUTPUT(DS18B20_DDR, DS18B20_BIT);
	LOW(DS18B20_PORT, DS18B20_BIT);
	_delay_us(1);

	INPUT(DS18B20_DDR, DS18B20_BIT);
	_delay_us(14);

	bit = IS_HIGH(DS18B20_PIN, DS18B20_BIT);
	_delay_us(45);

	return (bit);
}

void
ds18b20_write_byte(uint8_t byte)
{
	uint8_t i = 8;

	while (i--)
	{
		ds18b20_write_bit(byte&1);
		byte >>= 1;
	}
}

uint8_t
ds18b20_read_byte(void)
{
	uint8_t ret = 0;
	uint8_t i = 8;

	while (i--)
	{
		ret >>= 1;
		ret |= (ds18b20_read_bit() << 7);
	}

	return (ret);
}

double
ds18b20_read_temp()
{
	uint8_t lo, hi;
	double ret;

#if DS18B20_STOPINTERRUPTONREAD == 1
	cli();
#endif

	ds18b20_reset();

	ds18b20_write_byte(DS18B20_CMD_SKIPROM);
	ds18b20_write_byte(DS18B20_CMD_CONVERTTEMP);

	// wait for conversion
	while (!ds18b20_read_bit());

	ds18b20_reset();
	ds18b20_write_byte(DS18B20_CMD_SKIPROM);
	ds18b20_write_byte(DS18B20_CMD_RSCRATCHPAD);

	lo = ds18b20_read_byte();
	hi = ds18b20_read_byte();

#if DS18B20_STOPINTERRUPTONREAD == 1
	sei();
#endif

	//convert the 12 bit value obtained
	ret = ((hi << 8) + lo) * 0.0625;

	return (ret);
}
