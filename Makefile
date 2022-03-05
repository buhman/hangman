all: main.gba

#$(LD) -r -b binary $< -o $@

define BUILD_BINARY_O
	$(OBJCOPY) \
		-I binary -O elf32-littlearm -B armv4t \
		--rename-section .data=.rodata,alloc,load,readonly,data,contents \
		$< $@
endef

define LINK_ELF
	$(LD) --print-memory-usage -Map=$@.map -T main.lds $^ -o $@
endef

%.txt.o: %.txt
	$(BUILD_BINARY_O)

%.binlst.o: %.binlst
	$(BUILD_BINARY_O)

%.data.o: %.data
	$(BUILD_BINARY_O)

%.glyph.o: %.glyph
	$(BUILD_BINARY_O)

.PHONY: make-tools

make-tools:
	$(MAKE) -C tools

DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

%.glyph: %.otb | make-tools
	$(DIR)/tools/otb-convert $< > $@

%.binlst: %.txt | make-tools
	$(DIR)/tools/word-convert < $< > $@

OBJS = header.o load.o main.o copy.o glyph.o keyboard.o hang.o xorshift.o
OBJS += res/font_8x8.glyph.o
OBJS += res/font_8x16.glyph.o
OBJS += res/words.binlst.o

main.elf: $(OBJS) | main.lds
	$(LINK_ELF)

include common.mk
