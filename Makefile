# Project Details
PROJ:= game
EXT := gba
UDIR := ./source

CFILES := $(foreach dir,$(UDIR),$(wildcard $(dir)/*.c))

COBJS := $(CFILES:.c=.o)
OBJS := $(COBJS)

# Tool Settings
CROSS:=arm-none-eabi-
AS:=$(CROSS)as
CC:=$(CROSS)gcc
LD:=$(CROSS)gcc
OBJCOPY:=$(CROSS)objcopy

MODEL:=-mthumb -mthumb-interwork 
SPECS:=-specs=gba.specs

CFLAGS:= $(MODEL) -O2 -Wall -fno-strict-aliasing -Iinclude
LDFLAGS:= $(MODEL) $(SPECS)

#Build Steps
$(PROJ).$(EXT): $(PROJ).elf
	$(OBJCOPY) -O binary $< $@
	gbafix $@

$(PROJ).elf: $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

# clean
.PHONY: clean
clean:
	@rm -fv $(COBJS)
	@rm -fv $(PROJ).$(EXT)
	@rm -fv $(PROJ).elf
