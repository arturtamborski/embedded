#ifndef DS18B20_H
#define DS18B20_H

#include <avr/io.h>

#define DS18B20_PORT 	PORTC
#define DS18B20_DDR 	DDRC
#define DS18B20_PIN 	PINC
#define DS18B20_BIT 	PC0

#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define DS18B20_CMD_SEARCHROM 0xf0
#define DS18B20_CMD_READROM 0x33
#define DS18B20_CMD_MATCHROM 0x55
#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_ALARMSEARCH 0xec

#define DS18B20_STOPINTERRUPTONREAD 1

uint8_t ds18b20_reset(void);
void 	ds18b20_write_byte(uint8_t byte);
uint8_t ds18b20_read_byte(void);
double 	ds18b20_read_temp(void);

#endif // DS18B20_H
