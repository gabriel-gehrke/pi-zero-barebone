BOOTMNT ?= /media/parallels/boot

CC = gcc
COPS = -Wall -Werror -O1 -nostdlib -nostartfiles -ffreestanding -Iinclude \
		 -marm -mcpu=arm1176jzf-s

AOPS = -Iinclude --warn --fatal-warnings

BUILD_DIR = build
SRC_DIR = src

all: kernel.img

clean:
	rm -rf $(BUILD_DIR) *.img *.elf

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_S.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(CC) $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.s
	mkdir -p $(@D)
	as $(AOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s)
ASM_PREPROC_FILES = $(wildcard $(SRC_DIR)/*.S)

OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(ASM_PREPROC_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_S.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel.elf: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo "Building kernel.elf..."
	ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel.elf $(OBJ_FILES)

kernel.img: kernel.elf
	@echo "Exporting image..."
	objcopy $(BUILD_DIR)/kernel.elf -O binary $(BUILD_DIR)/kernel.img
	sync
