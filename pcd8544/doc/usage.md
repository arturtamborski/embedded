# PCD8544 Driver Library

## Usage

In order to use this library you'll have to copy the source code of it
to your project and recompile it with modified header file for your own configuration.

The header file `pcd8544.h` is well documented but here's a rundown of things 
that you might want to change:

### The `PCD8544_CMD_DEFAULT_*` macros
This library offers you the ability to change the default values for different 
parameters of the screen used when `pcd8544_init()` function is called.
One important thing to note is to keep the values defined there in the ranged
defined in macros. The ranges are inclusive on both sides.

### The `PCD8544_*_BUS/_BIT` macros
These are used for describing the connections between the screen and microprocessor.

### The `PCD8544_CHARACTER_WIDTH/HEIGHT` macros
These are strongly tied to the `pcd8544_font` array defined in `pcd8544_font.h` header file
so you should change them only with respect to the font file.

### The `PCD8544_CHARACTER_SPACING` macro
This macro will enlarge the space between the letters.

### The `PCD8544_BUFFERED` macro
This macro is the most important one because it defines how a library should behave internally.
If its switched on (the value is set to 1) then you are also allowed to use few additional
functions for easier control over the screen and buffer.
Note: if you've turned this on but nothing happens then check if you're calling the `pcd8544_draw()` function which accually sends the buffer to the screen.

### The `PCD8544_PROGMEM` macro
This one should be turned on by default because it optimizes the memory footprint of the code.
