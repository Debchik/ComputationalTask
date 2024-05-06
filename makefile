.PHONY: all clean

all: Integrate

clean:
	rm -rf *.o

functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm

main.o: main.c
	gcc -m32 -std=c99 -c -o main.o main.c

Integrate: main.o functions.o
	gcc -m32 -std=c99 -o Integrate main.o functions.o -lm
