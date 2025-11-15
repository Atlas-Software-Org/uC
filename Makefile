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

clean:
	@rm -rf $(OUTMC)/obj $(LIBA) $(LIBSO)

.PHONY: clean all Headers

confirm-yes:
	@printf "Proceed? [Y/n] "
	@read ans; \
	ans=$${ans:-Y}; \
	if [ "$$ans" = "Y" ] || [ "$$ans" = "y" ]; then \
		echo "You chose YES"; \
	else \
		echo "You chose NO"; \
	fi

install_mccc:
	@install -m 755 ./mccc /usr/local/bin/mccc
	@echo "CP      ./mccc /usr/local/bin/mccc"
	@echo "Installed MCCC. Run MCCC with `mccc` command"

install:
	@printf "(Requires sudo) Proceed with installation? This process might be irreversible. [Y/n] "
	@read ans; \
	ans=$${ans:-Y}; \
	if [ "$$ans" = "Y" ] || [ "$$ans" = "y" ]; then \
		sudo mkdir -p /usr/local/include/mc/; \
		echo "MKDIR   /usr/local/include/mc/"; \
		sudo mkdir -p /usr/local/lib/mc/; \
		echo "MKDIR   /usr/local/lib/mc/"; \
		sudo cp -rf $(OUTMC)/inc/freestanding/* /usr/local/include/mc/; \
		echo "CP      $(OUTMC)/inc/freestanding/* /usr/local/include/mc/"; \
		sudo cp -rf $(OUTMC)/inc/hosted/* /usr/local/include/mc/; \
		echo "CP      $(OUTMC)/inc/hosted/* /usr/local/include/mc/"; \
		sudo cp -rf $(OUTMC)/libs/* /usr/local/lib/mc/; \
		echo "CP      $(OUTMC)/libs/* /usr/local/lib/mc/"; \
		echo "FINISH  Installed μC successfully"; \
		$(MAKE) install_mccc; \
	else \
		echo "Process cancelled."; \
	fi

clean_install:
	@printf "(Requires sudo) Proceed with cleaning installation? This process might be irreversible. [Y/n] "
	@read ans; \
	ans=$${ans:-Y}; \
	if [ "$$ans" = "Y" ] || [ "$$ans" = "y" ]; then \
		sudo rm -rf /usr/local/include/mc/; \
		echo "RM      /usr/local/include/mc/"; \
		sudo rm -rf /usr/local/lib/mc/; \
		echo "RM      /usr/local/lib/mc/"; \
		sudo rm -f /usr/local/bin/mccc; \
		echo "RM      /usr/local/bin/mccc"; \
		echo "FINISH  Deleted μC successfully"; \
	else \
		echo "Process cancelled."; \
	fi
