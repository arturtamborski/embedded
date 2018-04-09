/*** pcd8544.c
 * Library for PCD8544 matrix LCD controller used in nokia 5110/3310 screens.
 * docs: http://www.geeetech.com/Documents/Nokia5110%20datasheet.pdf
 * author: Artur Tamborski, @arturtamborski
 * source: https://github.com/arturtamborski/embeded/pcd8544/
 */
#include <avr/io.h>

#include "../util/util.h"
#include "pcd8544.h"


#if PCD8544_PROGMEM
#include <avr/pgmspace.h>
static const unsigned char pcd8544_font[][PCD8544_CHARACTER_WIDTH] PROGMEM =
#else
static const unsigned char pcd8544_font[][PCD8544_CHARACTER_WIDTH] =
#endif
{
#include "pcd8544_font.h"
};


#if PCD8544_BUFFERED
static struct pcd8544_buffer
{
	uint8_t x, y;
	uint8_t data[PCD8544_SCREEN_BYTES];
} pcd8544_buffer;
#endif


static inline void
_shift_byte_msb(uint8_t data)
{
	register uint8_t i = 8;
	register uint8_t bit;

	while (i--)
	{
		bit = (data & 0x80) >> 7;
		data <<= 1;

		// DIN_BIT is set to the value of `bit` without 
		// modifing other PORT bits
		PORT(PCD8544_DIN_BUS) ^= 
			(-bit ^ PORT(PCD8544_DIN_BUS)) 
			& (1 << PCD8544_DIN_BIT);

		// Pulse the clock.
		// note: You might want to add a delay between these
		//       macros but from what I've tested its not required.
		HIGH_PORT(PCD8544_CLK_BUS, PCD8544_CLK_BIT);
		LOW_PORT(PCD8544_CLK_BUS, PCD8544_CLK_BIT);
	}
}


void
pcd8544_init(void)
{
	OUTPUT_DDR(PCD8544_RST_BUS, PCD8544_RST_BIT);
	OUTPUT_DDR(PCD8544_DIN_BUS, PCD8544_DIN_BIT);
	OUTPUT_DDR(PCD8544_CLK_BUS, PCD8544_CLK_BIT);
	OUTPUT_DDR(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
	OUTPUT_DDR(PCD8544_DC_BUS, PCD8544_DC_BIT);

	// Pulse the reset for initialization.
	// note: You might want to add a delay between these
	//       macros but from what I've tested its not required.
	LOW_PORT(PCD8544_RST_BUS, PCD8544_RST_BIT);
	HIGH_PORT(PCD8544_RST_BUS, PCD8544_RST_BIT);

	pcd8544_send_cmd(PCD8544_CMD_EXTENDED_MODE);
	pcd8544_send_cmd(PCD8544_CMD_MASK_TEMPERATURE
		| PCD8544_CMD_DEFAULT_TEMPERATURE);
	pcd8544_send_cmd(PCD8544_CMD_MASK_CONTRAST
		| PCD8544_CMD_DEFAULT_CONTRAST);
	pcd8544_send_cmd(PCD8544_CMD_MASK_BIAS
		| PCD8544_CMD_DEFAULT_BIAS);
	pcd8544_send_cmd(PCD8544_CMD_BASIC_MODE);
	
	// This shift is required for correct bit pattern.
	pcd8544_send_cmd(PCD8544_CMD_MASK_DISPLAY_MODE
		| ((PCD8544_CMD_DEFAULT_DISPLAY_MODE & 0x02) << 1
		| PCD8544_CMD_DEFAULT_DISPLAY_MODE));

	pcd8544_clear();
}


void
pcd8544_send_cmd(uint8_t cmd)
{
	LOW_PORT(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
	LOW_PORT(PCD8544_DC_BUS, PCD8544_DC_BIT);

	_shift_byte_msb(cmd);

	HIGH_PORT(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
}


void
pcd8544_send_data(uint8_t data)
{
#if PCD8544_BUFFERED
	pcd8544_buffer.data[PCD8544_SCREEN_WIDTH
		* pcd8544_buffer.y
		+ pcd8544_buffer.x] = data;

	pcd8544_buffer.x++;
	if (pcd8544_buffer.x > PCD8544_SCREEN_WIDTH)
		pcd8544_buffer.x = 0, pcd8544_buffer.y++;
#else
	LOW_PORT(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
	HIGH_PORT(PCD8544_DC_BUS, PCD8544_DC_BIT);

	_shift_byte_msb(data);

	HIGH_PORT(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
#endif
}


void
pcd8544_draw(void)
{
#if PCD8544_BUFFERED
	uint16_t i;

	// Reset position because the code below fills the whole screen at once.
	pcd8544_set_xy(0, 0);

	LOW_PORT(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
	HIGH_PORT(PCD8544_DC_BUS, PCD8544_DC_BIT);

	for (i = 0; i < PCD8544_SCREEN_BYTES; i++)
		_shift_byte_msb(pcd8544_buffer.data[i]);

	HIGH_PORT(PCD8544_SCE_BUS, PCD8544_SCE_BIT);
#endif
}


void
pcd8544_fill(char c)
{
	uint8_t i = PCD8544_NUM_LINES * PCD8544_NUM_CHARACTERS;

	while (i--)
		pcd8544_putc(c);

	pcd8544_set_xy(0, 0);
}


void
pcd8544_fill_line(char c)
{
#if PCD8544_BUFFERED
	uint8_t x, y;

	x = pcd8544_buffer.x;
	y = pcd8544_buffer.y;

	pcd8544_set_xy(0, y);
	pcd8544_fill_chars(c, PCD8544_NUM_CHARACTERS);
	pcd8544_set_xy(x, y);
#endif
}


void
pcd8544_fill_chars(char c, uint8_t n)
{
#if PCD8544_BUFFERED
	uint8_t x, y;

	x = pcd8544_buffer.x;
	y = pcd8544_buffer.y;

	while (n--)
		pcd8544_putc(c);

	pcd8544_set_xy(x, y);
#endif
}


void
pcd8544_fill_bytes(uint8_t b, uint16_t n)
{
#if PCD8544_BUFFERED
	uint8_t x, y;

	x = pcd8544_buffer.x;
	y = pcd8544_buffer.y;

	while (n--)
		pcd8544_send_data(b);

	pcd8544_set_xy(x, y);
#endif
}


void
pcd8544_clear(void)
{
	pcd8544_fill(' ');
}


void
pcd8544_clear_line(void)
{
#if PCD8544_BUFFERED
	pcd8544_fill_line(' ');
#endif
}


void
pcd8544_clear_chars(uint8_t n)
{
#if PCD8544_BUFFERED
	pcd8544_fill_chars(' ', n);
#endif
}


void
pcd8544_clear_bytes(uint16_t n)
{
#if PCD8544_BUFFERED
	pcd8544_fill_bytes(0x00, n);
#endif
}


void
pcd8544_putc(char c)
{
	uint8_t byte;
	uint8_t i;

	for (i = 0; i < PCD8544_CHARACTER_WIDTH; i++)
	{
#if PCD8544_PROGMEM
		byte = pgm_read_byte(&pcd8544_font[c - 0x20][i]);
#else
		byte = pcd8544_font[c - 0x20][i];
#endif
		pcd8544_send_data(byte);
	}

#if PCD8544_CHARACTER_SPACING 
	pcd8544_send_data(0x00);
#endif
}


void
pcd8544_puts(char *s)
{
	while (*s)
		pcd8544_putc(*s++);
}


void
pcd8544_puti(int8_t i)
{
	if (i < 0)
		pcd8544_putc('-');

	pcd8544_putu(~i + 1);
}


void
pcd8544_putu(uint8_t u)
{
	char buf[4];
	char *p = buf;

	do
		*p++ = (u % 10) + 0x30;
	while (u /= 10);

	do
		pcd8544_putc(*--p);
	while (p != buf);
}


void
pcd8544_putrn(void)
{
#if PCD8544_BUFFERED
	pcd8544_set_pos(0, pcd8544_buffer.y + 1);
#endif
}


void pcd8544_set_pos(uint8_t x, uint8_t y)
{
	x *= PCD8544_CHARACTER_WIDTH + PCD8544_CHARACTER_SPACING;

	pcd8544_set_xy(x, y);
}


void
pcd8544_set_xy(uint8_t x, uint8_t y)
{
#if PCD8544_BUFFERED
	pcd8544_buffer.x = x;
	pcd8544_buffer.y = y;
#endif
	pcd8544_send_cmd(PCD8544_CMD_MASK_X_ADDRESS | x);
	pcd8544_send_cmd(PCD8544_CMD_MASK_Y_ADDRESS | y);
}


void
pcd8544_set_display_mode(uint8_t mode)
{
	// This shift is required for correct bit pattern.
	pcd8544_send_cmd(PCD8544_CMD_MASK_DISPLAY_MODE
		| ((mode & 0x2) << 1 | mode));
}


void
pcd8544_set_temperature(uint8_t value)
{
	pcd8544_send_cmd(PCD8544_CMD_EXTENDED_MODE);
	pcd8544_send_cmd(PCD8544_CMD_MASK_TEMPERATURE | value);
	pcd8544_send_cmd(PCD8544_CMD_BASIC_MODE);
}


void
pcd8544_set_contrast(uint8_t value)
{
	pcd8544_send_cmd(PCD8544_CMD_EXTENDED_MODE);
	pcd8544_send_cmd(PCD8544_CMD_MASK_CONTRAST | value);
	pcd8544_send_cmd(PCD8544_CMD_BASIC_MODE);
}


void
pcd8544_set_bias(uint8_t value)
{
	pcd8544_send_cmd(PCD8544_CMD_EXTENDED_MODE);
	pcd8544_send_cmd(PCD8544_CMD_MASK_BIAS | value);
	pcd8544_send_cmd(PCD8544_CMD_BASIC_MODE);
}
