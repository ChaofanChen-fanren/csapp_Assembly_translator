CC = gcc
CFLAGS = -Wall -g -O2 -Werror -std=gnu99 -Wno-unused-function

TARGET_HARDWARE = ./bin/test_hardware
TARGET_ELE = ./bin/test_elf

SRC_DIR = ../src

# debug
COMMON = $(SRC_DIR)/common/print.c $(SRC_DIR)/common/convert.c

# hardware
CPU =$(SRC_DIR)/hardware/cpu/mmu.c $(SRC_DIR)/hardware/cpu/isa.c
MEMORY = $(SRC_DIR)/hardware/memory/dram.c
LINKER = $(SRC_DIR)/linker/parseElf.c $(SRC_DIR)/linker/staticlink.c
# main
TEST_HARDWARE = $(SRC_DIR)/tests/test_hardware.c
TEST_ELF = $(SRC_DIR)/tests/test_elf.c

.PHONY:hardware
hardware:
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(COMMON) $(CPU) $(MEMORY) $(LINKER) $(TEST_HARDWARE) -o $(TARGET_HARDWARE)
	./$(TARGET_HARDWARE)

clean:
	rm -f *.o *~ $(TARGET_ELE)
