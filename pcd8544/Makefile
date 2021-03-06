TARGET  = $(notdir $(CURDIR)).hex

PORT    = /dev/ttyUSB0
SPEED   = 9600

CPU     = m32
MMCU    = atmega32a
F_CPU   = 8000000
BAUD    = 9600

SRCEXT  = .c
INCEXT  = .h
OBJEXT  = .o

SRCDIR  = src
INCDIR  = src
OBJDIR  = bin

CC      = avr-gcc
LD      = avr-gcc

CCFLAGS = -Os -DBAUD=$(BAUD) -DF_CPU=$(F_CPU)UL
LDFLAGS =
PGFLAGS = 

SRCTREE = $(shell find $(SRCDIR) -type d)
INCS    = $(shell find $(INCDIR) -type f -name '*$(INCEXT)')
SRCS    = $(shell find $(SRCDIR) -type f -name '*$(SRCEXT)')
OBJTREE = $(foreach D,$(SRCTREE),$(shell echo $(D) | sed 's/$(SRCDIR)/$(OBJDIR)/'))
OBJSTMP = $(foreach F,$(SRCS),$(shell echo $(F) | sed -e 's/$(SRCDIR)/$(OBJDIR)/'))
OBJS    = $(foreach F,$(OBJSTMP),$(shell echo $(F) | sed -e 's/\$(SRCEXT)/\$(OBJEXT)/'))


all: $(TARGET)
	@echo Done.

run: $(TARGET)
	@avrdude $(PGFLAGS) -c usbasp -p $(CPU) -P $(PORT) -b $(SPEED) -U flash:w:$(TARGET)

clean:
	@rm -r $(OBJDIR)/$(TARGET:.hex=.elf) $(TARGET) $(OBJS) $(OBJDIR) 2>/dev/null || true

$(TARGET): $(OBJS) | $(OBJDIR)
	@$(LD) -mmcu=$(MMCU) $(LDFLAGS) -L$(OBJDIR) -o $(OBJDIR)/$(@:.hex=.elf) $^
	@avr-objcopy -O ihex $(OBJDIR)/$(@:.hex=.elf) $(TARGET)

$(OBJS): $(OBJDIR)/%$(OBJEXT) : $(SRCDIR)/%$(SRCEXT) | $(OBJDIR)
	@$(CC) -mmcu=$(MMCU) $(CCFLAGS) -I$(INCDIR) -c -o $@ $?

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(OBJTREE)

.PHONY: all run clean
