/*** pcd8544.h
 * Library for PCD8544 matrix LCD controller used in nokia 5110/3310 screens.
 * docs: http://www.geeetech.com/Documents/Nokia5110%20datasheet.pdf
 * author: Artur Tamborski, @arturtamborski
 * source: https://github.com/arturtamborski/embeded/pcd8544/
 */
#ifndef PCD8544_H
#define PCD8544_H


/*** Width of the screen.
 */
#define PCD8544_SCREEN_WIDTH 84


/*** Half the width of the screen.
 */
#define PCD8544_HALF_SCREEN_WIDTH (PCD8544_SCREEN_WIDTH / 2)


/*** Height of the screen.
 */
#define PCD8544_SCREEN_HEIGHT 48


/*** Half the height of the screen.
 */
#define PCD8544_HALF_SCREEN_HEIGHT (PCD8544_SCREEN_HEIGHT / 2)


/*** Total number of pixels on the screen.
 */
#define PCD8544_SCREEN_PIXELS (PCD8544_SCREEN_WIDTH * PCD8544_SCREEN_HEIGHT)


/*** Total number of bytes on the screen.
 */
#define PCD8544_SCREEN_BYTES (PCD8544_SCREEN_PIXELS / 8)


/*** Total number of lines on the screen.
 */
#define PCD8544_NUM_LINES (PCD8544_SCREEN_HEIGHT / PCD8544_CHARACTER_HEIGHT)


/*** Total number of characters in one line.
 */
#define PCD8544_NUM_CHARACTERS \
	(PCD8544_SCREEN_WIDTH / \
	(PCD8544_CHARACTER_WIDTH + PCD8544_CHARACTER_SPACING))


/*** Controller modes.
 */
#define PCD8544_CMD_BASIC_MODE 0x20
#define PCD8544_CMD_EXTENDED_MODE 0x21


/*** Masks.
 */
#define PCD8544_CMD_MASK_DISPLAY_MODE 0x08
#define PCD8544_CMD_MASK_TEMPERATURE 0x04
#define PCD8544_CMD_MASK_CONTRAST 0x80
#define PCD8544_CMD_MASK_BIAS 0x10
#define PCD8544_CMD_MASK_X_ADDRESS 0x80
#define PCD8544_CMD_MASK_Y_ADDRESS 0x40


/*** Display modes.
 */
#define PCD8544_CMD_DISPLAY_MODE_BLANK 0
#define PCD8544_CMD_DISPLAY_MODE_NORMAL 1
#define PCD8544_CMD_DISPLAY_MODE_ALL_SEGMENTS 2
#define PCD8544_CMD_DISPLAY_MODE_INVERSE 3


/*** Configuration.
 * You can modify the macros below.
 */


/*** Default display mode.
 * [0..3]. Values correspond with display modes macros above.
 */
#define PCD8544_CMD_DEFAULT_DISPLAY_MODE 2


/*** Default screen temperature.
 * [0..3].
 */
#define PCD8544_CMD_DEFAULT_TEMPERATURE 2


/*** Default screen contrast.
 * [0..127].
 */
#define PCD8544_CMD_DEFAULT_CONTRAST 60


/*** Default screen bias.
 * [0..7].
 */
#define PCD8544_CMD_DEFAULT_BIAS 4


/*** Connection settings.
 * This library uses macros from util/util.h for easier configuration.
 * *_BUS: any port letter, for PORTC it would be set to C.
 * *_BIT: any port number, for PC1 it would be set to 1.
 */
#define PCD8544_RST_BUS D
#define PCD8544_RST_BIT 0

#define PCD8544_DIN_BUS D
#define PCD8544_DIN_BIT 3

#define PCD8544_CLK_BUS D
#define PCD8544_CLK_BIT 4

#define PCD8544_SCE_BUS D
#define PCD8544_SCE_BIT 1

#define PCD8544_DC_BUS D
#define PCD8544_DC_BIT 2


/*** Character width in font array.
 * This value should meet the following equation for even character spacing:
 * SCREEN_WIDTH % (CHARACTER_WIDTH + CHARACTER_SPACING) == 0
 * note: Generally, keep it set to 5 if CHARACTER_SPACING is 1.
 *       Otherwise set it to required value but also update the font array 
 *       so that every character is as wide as new value.
 */
#define PCD8544_CHARACTER_WIDTH 5


/*** Character height in font array.
 * This value should meet the following equation for even line spacing:
 * SCREEN_HEIGHT % CHARACTER_HEIGHT == 0
 * note: Generally, keep it set to 8. Otherwise set it to required value,
 *       but also update the font array so that every character is 
 *       as high as new value.
 * note: if this value is bigger than 8 and BUFFERED is 0 then
 *       every character will be drawn in two separate lines.
 */
#define PCD8544_CHARACTER_HEIGHT 8


/*** Switch for character spacing.
 * This will print additional pixel wide bar after each character
 * for improved readability. This also reduces the font array size.
 */
#define PCD8544_CHARACTER_SPACING 0


/*** Switch for screen buffering.
 * More efficient, but takes more RAM for buffer (506 bytes).
 * note: Use this when the screen content changes frequently (e.g. GUI)
 *       But you probably want this to be turned off,
 *       because the gained speed is not worth so much memory.
 */
#define PCD8544_BUFFERED 0


/*** Switch for storing font in PROGMEM.
 * A bit less efficient, but takes PROGMEM instead of RAM for font.
 * note: You probably want this to be turned on, 
 *       because AVRs have way more ROM (PROGMEM) than RAM.
 */
#define PCD8544_PROGMEM 1


/*** Inits the screen.
 */
void pcd8544_init(void);


/*** Sends command to the screen.
 * cmd: command to send.
 * note: This function ignores buffering.
 */
void pcd8544_send_cmd(uint8_t cmd);


/*** Sends data to the screen.
 * data: byte to send.
 */
void pcd8544_send_data(uint8_t data);


/*** Draws the buffer to the screen.
 * This function works only in BUFFERED mode.
 * When _BUFFERED is on, then only this function can draw on screen.
 */
void pcd8544_draw(void);


/*** Fills the screen.
 * c: char to fill with.
 */
void pcd8544_fill(char c);


/*** Fills the line.
 * c: char to fill with.
 * This function works only in BUFFERED mode.
 */
void pcd8544_fill_line(char c);


/*** Fills the number of characters in line.
 * c: char to fill with.
 * n: number of characters to fill.
 * This function works only in BUFFERED mode.
 */
void pcd8544_fill_chars(char c, uint8_t n);


/*** Fills the number of bytes in line.
 * b: byte to fill with.
 * n: number of bytes to fill.
 * This function works only in BUFFERED mode.
 */
void pcd8544_fill_bytes(uint8_t b, uint16_t n);


/*** Clears the screen.
 */
void pcd8544_clear(void);


/*** Clears the line.
 * This function works only in BUFFERED mode.
 * note: It returns cursor to previous position on exit.
 */
void pcd8544_clear_line(void);

/*** Clears the number of characters in line.
 * n: number of characters to clear.
 * This function works only in BUFFERED mode.
 */
void pcd8544_clear_chars(uint8_t n);


/*** Clears the number of bytes in line.
 * n: number of bytes to clear.
 * This function works only in BUFFERED mode.
 */
void pcd8544_clear_bytes(uint16_t n);


/*** Puts the character on the screen.
 * c: character to put.
 * note: this function can't use PROGMEM strings.
 */
void pcd8544_putc(char c);


/*** Puts the string on the screen.
 * s: pointer to string.
 * note: this function can't use PROGMEM strings.
 */
void pcd8544_puts(char *s);


/*** Puts the integeer on the screen.
 * i: integer to put.
 * note: this will print the decimal in base 10 form.
 */
void pcd8544_puti(int8_t i);


/*** Puts the unsigned integeer on the screen.
 * u: integer to put.
 * note: this will print the decimal in base 10 form.
 */
void pcd8544_putu(uint8_t u);


/*** Goes to next line and returns cursor to start of the line.
 * This function works only in BUFFERED mode.
 * note: The driver doesn't support reading current address
 *       and the library doesn't perserve any hidden internal 
 *       states which makes relative addressing impossible.
 */
void pcd8544_putrn(void);


/*** Sets the next character position.
 * x: [0..NUM_CHARACTERS] (for default settings: [0..14])
 * y: [0..NUM_LINES] (for default settings: [0..5])
 */
void pcd8544_set_pos(uint8_t x, uint8_t y);


/*** Sets the next byte position.
 * x: [0..83]
 * y: [0..5]
 */
void pcd8544_set_xy(uint8_t x, uint8_t y);


/*** Sets display mode.
 * mode: [0..3] (0: blank, 1: normal, 2: all segments, 3: inverse).
 * More information can be found in datasheet on page 14.
 */
void pcd8544_set_display_mode(uint8_t mode);


/*** Sets the screen temperature.
 * value: [0..3]
 */
void pcd8544_set_temperature(uint8_t value);


/*** Sets the screen contrast.
 * value: [0..127]
 */
void pcd8544_set_contrast(uint8_t value);


/*** Sets sects the bias.
 * value: [0..7]
 */
void pcd8544_set_bias(uint8_t value);


#endif
