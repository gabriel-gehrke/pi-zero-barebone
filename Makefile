BOOTMNT ?= /media/parallels/boot

ARCH = $(shell uname -p | head -c 3)

ifeq ($(ARCH), arm)
	CC = gcc
	AS = as
	LD = ld
	OBJCPY = objcopy
	OBJDUMP = objdump
else
	CC = arm-linux-gnueabihf-gcc
	AS = arm-linux-gnueabihf-as
	LD = arm-linux-gnueabihf-ld
	OBJCPY = arm-linux-gnueabihf-objcopy
	OBJDUMP = arm-linux-gnueabihf-objdump
endif

COPS = -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -Iinclude \
		 -marm -mgeneral-regs-only \
		 -march=armv6zk -mcpu=arm1176jzf-s -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard

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
	$(AS) $(AOPS) -MMD -c $< -o $@

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
	$(LD) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel.elf $(OBJ_FILES)

kernel.img: kernel.elf
	@echo "Exporting image..."
	$(OBJDUMP) $(BUILD_DIR)/kernel.elf -D > $(BUILD_DIR)/kernel.dump
	$(OBJCPY) $(BUILD_DIR)/kernel.elf -O binary $(BUILD_DIR)/kernel.img
	sync
