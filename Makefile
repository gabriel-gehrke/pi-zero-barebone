BOOTMNT ?= /media/parallels/boot

CC = arm-none-eabi
COPS = -Wall -Werror -O1 -nostdlib -nostartfiles -ffreestanding -Iinclude \
		 -marm

AOPS = -Iinclude --warn --fatal-warnings

BUILD_DIR = build
SRC_DIR = src

all: kernel.img

clean:
	rm -rf $(BUILD_DIR) *.img *.elf

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.s
	mkdir -p $(@D)
	$(CC)-as $(AOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.s)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel.elf: $(SRC_DIR)/memmap $(OBJ_FILES)
	@echo "Building kernel.elf..."
	$(CC)-ld -T $(SRC_DIR)/memmap -o $(BUILD_DIR)/kernel.elf $(OBJ_FILES)

kernel.img: kernel.elf
	@echo "Exporting image..."
	$(CC)-objcopy --srec-forceS3 $(BUILD_DIR)/kernel.elf -O srec $(BUILD_DIR)/kernel.srec
	$(CC)-objcopy $(BUILD_DIR)/kernel.elf -O binary $(BUILD_DIR)/kernel.img
	sync
