BOOTMNT ?= /media/parallels/boot

CC = arm-none-eabi
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding -Iinclude -mgeneral-regs-only \
		-march=armv6+fp -marm

ASMOPS = -Iinclude

BUILD_DIR = build
SRC_DIR = src

all: kernel8.img

clean:
	rm -rf $(BUILD_DIR) *.img *.elf

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	mkdir -p $(@D)
	$(CC)-gcc $(COPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)


kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	@echo ""
	@echo "Building Raspberry Pi Zero bare metal OS..."
	@echo ""

	$(CC)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel.elf $(OBJ_FILES)
	$(CC)-objcopy $(BUILD_DIR)/kernel.elf -O binary $(BUILD_DIR)/kernel.img

	rm -rf $(BUILD_DIR)/config.txt
	cp config.txt $(BUILD_DIR)/config.txt
	sync
