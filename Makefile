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

all: $(LIBA) $(LIBSO) Headers

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

# Copy headers to output
Headers:
	@mkdir -p $(OUTMC)/inc/freestanding $(OUTMC)/inc/hosted
	@cp -rf $(INC)/freestanding/* $(OUTMC)/inc/freestanding/
	@cp -rf $(INC)/hosted/* $(OUTMC)/inc/hosted/
	@cp -f $(INC)/HELPERS.h $(OUTMC)/inc/

clean:
	@rm -rf $(OUTMC)/obj $(LIBA) $(LIBSO)

.PHONY: clean all Headers
