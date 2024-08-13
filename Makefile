# This is the name of your final .nex file without the .nex extension
EXEC_OUTPUT=build/ttcalc

# List all your source files here
SOURCES = ttcalc.c\
			modules/system_helper.c\
			modules/view_helper.c\
			modules/adt_cell.c\
			modules/adt_sheet.c

# Maybe you'll need to edit this

# ZX Spectrum
# CRT=1

#CP/M
CRT=3

# You don't need to edit below here, have a nice day.

MKDIR = mkdir -p
CC=docker run  --platform linux/amd64 -v .:/src/ -it z88dk/z88dk zcc
AS=docker run  --platform linux/amd64 -v .:/src/ -it z88dk/z88dk zcc
# TARGET=+zxn -subtype=nex -lndos -lm -DAMALLOC
TARGET=+zx -lndos -lm -DAMALLOC
# TARGET=+cpm -lndos -lzxcpm -lm -DAMALLOC -D__CPM__
VERBOSITY=-vn
OUT_DIR=build bin
PRAGMA_FILE=zpragma.inc

OBJECTS=$(SOURCES:.*=.o)
OBJS=$(patsubst %, src/%, $(OBJECTS))

C_OPT_FLAGS=-SO3 --max-allocs-per-node200000 --opt-code-size

CFLAGS=$(TARGET) $(VERBOSITY) -c $(C_OPT_FLAGS) -compiler sdcc -clib=ansi\
-pragma-define:ansicolumns=42 -pragma-redirect:CRT_FONT=_font_8x8_zx_clairsys
# -pragma-define:CRT_MODEL=2
# -pragma-define:CRT_ORG_CODE=0x8000
# -pragma-define:CRT_ORG_BSS=0xC000
# -pragma-define:CLIB_MALLOC_HEAP_SIZE=35840 
# -pragma-include:$(PRAGMA_FILE)
LDFLAGS=$(TARGET) $(VERBOSITY) --list -m -s -clib=ansi\
-pragma-define:ansicolumns=42 -pragma-redirect:CRT_FONT=_font_8x8_clairsys
# -pragma-define:CRT_MODEL=2
# -pragma-define:CRT_ORG_CODE=0x8000
# -pragma-define:CRT_ORG_BSS=0xC000
# -pragma-define:CLIB_MALLOC_HEAP_SIZE=23150 
# -pragma-include:$(PRAGMA_FILE)
ASFLAGS=$(TARGET) $(VERBOSITY) -c --list -m -s 
# EXEC=$(EXEC_OUTPUT).nex
EXEC=$(EXEC_OUTPUT).tap
# EXEC=$(EXEC_OUTPUT).com

%.o: %.c $(PRAGMA_FILE)
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

all : dirs $(EXEC)

$(EXEC) : $(OBJS)
	$(CC) $(LDFLAGS) -startup=$(CRT) $(OBJS) -o $(EXEC_OUTPUT) -create-app

.PHONY: clean dirs install

install: all
	mv $(EXEC) bin

clean:
	rm -rf $(OUT_DIR) /tmp/tmpXX*
	rm -f src/*.lis src/*.sym src/*.o \
		src/modules/*.lis src/modules/*.sym src/modules/*.o

dirs: $(OUT_DIR)

$(OUT_DIR):
	$(MKDIR) $(OUT_DIR)
