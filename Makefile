BOOTMNT ?= /media/parallels/boot

CC = gcc
COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only \
		-march=armv6

ASMOPS = -Iinclude

BUILD_DIR = ./build
SRC_DIR = ./src

all: kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.s
	mkdir -p $(@D)
	$(CC) $(COPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)


kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo "Building Raspberry Pi Zero bare metal OS..."
	@echo ""
	ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.img $(OBJ_FILES)
	rm -rf $(BUILD_DIR)/config.txt
	cp config.txt $(BUILD_DIR)/config.txt
	sync