
CFLAGS = -Wall -g -O2 -Werror -std=gnu99

EXE = program

SRC = ../src/

CODE = ./memory/instruction.c ./disk/code.c ./cpu/mmu.c ./memory/dram.c ./main.c 

.PHONY = program
main:
	gcc $(CFLAGS) -I$(SRC) $(CODE) -o $(EXE)

run:
	./$(EXE)
