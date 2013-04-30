###############################################################################
# Makefile for the project ATMega48_BID101_RX_SIMON
###############################################################################

## General Flags
PROJECT = ATMega48_BID101_RX_SIMON
MCU = atmega48
TARGET = ATMega48_BID101_RX_SIMON.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=ATMega48_BID101_RX_SIMON.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o rc5.o uart.o bluecore.o rc5_mode.o readuart.o key.o detectpin.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) ATMega48_BID101_RX_SIMON.hex ATMega48_BID101_RX_SIMON.eep ATMega48_BID101_RX_SIMON.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

rc5.o: ../rc5.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

bluecore.o: ../bluecore.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

rc5_mode.o: ../rc5_mode.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

readuart.o: ../readuart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

key.o: ../key.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

detectpin.o: ../detectpin.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) ATMega48_BID101_RX_SIMON.elf dep/* ATMega48_BID101_RX_SIMON.hex ATMega48_BID101_RX_SIMON.eep ATMega48_BID101_RX_SIMON.lss ATMega48_BID101_RX_SIMON.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

