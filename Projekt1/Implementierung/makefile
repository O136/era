#subdirs = src test

CC=gcc
CFLAGS = -Wall -m64 -std=gnu11

DEPS = headers/polynome.h headers/utils.h
SRCS = src/main.c src/utils.c src/norm.asm
OBJS = src/main.o src/utils.o src/norm.o

ASMC = nasm
ASM_FLAGS = -f elf64

#used for main program
all: norm.o main.o utils.o test
	CC CFLAGS -o out main.o utils.o

#test target, independent from all target
test:
	$CC $CFLAGS -c test/test.c -o test/test_bin

main.o: main.c
	$CC $FLAGS -c src/main.c

utils.o: utils.c
	$CC $CFLAGS -c src/utils.c

norm.o: norm.asm
	$ASMC $ASM_FLAGS -o norm.o

clean:
	rm src/*.o
	rm test/*.o
