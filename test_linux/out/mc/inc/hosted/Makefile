SRC := source
SYSDEPS := sysdeps
INC := include
OUTMC := out/mc
OUT:=$(OUTMC)

CC := gcc
OPTIMISATION := -Os
CFLAGS := -ffreestanding -nolibc -nostdlib -nostdinc -I./$(INC) -I./$(INC)/freestanding/ -I./$(INC)/hosted/ -fPIC \
           -fno-exceptions -fno-asynchronous-unwind-tables -fno-stack-protector

AR := ar
LD := ld

CFILES := $(shell find $(SRC) $(SYSDEPS) -name '*.c')
OBJ := $(patsubst %.c, $(OUTMC)/obj/%.o, $(CFILES))

LIBA := $(OUTMC)/libs/micro_c.a
LIBSO := $(OUTMC)/libs/micro_c.so

all: $(LIBA) $(LIBSO) Headers

$(OUTMC)/obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(OPTIMISATION) $(CFLAGS) -c $< -o $@
	@echo "CC      $<"

$(LIBA): $(OBJ)
	@mkdir -p $(dir $@)
	@$(AR) rcs $@ $^
	@echo "AR      $@"

$(LIBSO): $(OBJ)
	@mkdir -p $(dir $@)
	@$(LD) -shared -o $@ $^
	@echo "SO      $@"

Headers:
	mkdir -p ./$(OUT)/inc ./$(OUT)/inc/freestanding ./$(OUT)/inc/hosted
	cp -rf ./$(INC)/freestanding/* ./$(OUT)/inc/freestanding/
	cp -rf ./$(INC)/hosted/* ./ ./$(OUT)/inc/hosted

clean:
	rm -rf $(OUTMC)/obj $(LIBA) $(LIBSO)

.PHONY: clean all
