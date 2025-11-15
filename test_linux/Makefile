SRC := source
SYSDEPS := sysdeps
INC := include
OUTMC := out/mc

CC := gcc
OPTIMISATION := -Os
CFLAGS := -ffreestanding -nolibc -nostdlib -nostdinc \
           -I./$(INC) -I./$(INC)/freestanding/ -I./$(INC)/hosted/ \
           -fPIC -fno-exceptions -fno-asynchronous-unwind-tables -fno-stack-protector

AR := ar

CFILES := $(shell find $(SRC) $(SYSDEPS) -name '*.c')
OBJ := $(patsubst %.c, $(OUTMC)/obj/%.o, $(CFILES))

LIBA := $(OUTMC)/libs/micro_c.a
LIBSO := $(OUTMC)/libs/micro_c.so

all: $(LIBA) $(LIBSO) Headers CRT

# Compile each .c file to .o
$(OUTMC)/obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(OPTIMISATION) $(CFLAGS) -c $< -o $@
	@echo "CC      $<"

# Build static library
$(LIBA): $(OBJ)
	@mkdir -p $(dir $@)
	@$(AR) rcs $@ $^
	@echo "AR      $@"

# Build shared library
$(LIBSO): $(OBJ)
	@mkdir -p $(dir $@)
	@$(CC) -shared $(OBJ) -o $@ $(CFLAGS)
	@echo "SO      $@"

CRT:
	@mkdir -p $(OUTMC)/crt/
	@nasm -f elf64 crt/crt0.asm -o $(OUTMC)/crt/crt0.o
	@echo "NASM    crt/crt0.asm"
	@nasm -f elf64 crt/crt1.asm -o $(OUTMC)/crt/crt1.o
	@echo "NASM    crt/crt1.asm"

# Copy headers to output
Headers:
	@mkdir -p $(OUTMC)/inc/freestanding $(OUTMC)/inc/hosted
	@cp -rf $(INC)/freestanding/* $(OUTMC)/inc/freestanding/
	@cp -rf $(INC)/hosted/* $(OUTMC)/inc/hosted/
	@cp -f $(INC)/HELPERS.h $(OUTMC)/inc/

clean:
	@rm -rf $(OUTMC)/obj $(LIBA) $(LIBSO)

.PHONY: clean all Headers
