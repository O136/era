CC=gcc
CFLAGS = -Wall -m64 -std=gnu11 -I headers

ASM = nasm
ASM_FLAGS = -f elf64

#used for main program
all: norm.o test
	$(CC) $(CFLAGS) -o main.out src/main.c src/utils.c src/norm.o

test: norm.o
	$(CC) $(CFLAGS) test/test.c src/utils.c src/norm.o -o test/test.out

norm.o: src/norm.asm
	$(ASM) $(ASM_FLAGS) src/norm.asm

clean:
	rm -f src/*.o
	rm -f src/*.out
	rm -f test/*.o
	rm -f test/*.out
	rm -f *.out
