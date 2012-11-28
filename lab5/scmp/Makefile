.PHONY: all clean
.SUFFIXES: .c .o .h .asm
CFLAGS=-g -m32 -O0 -Wall
LDFLAGS=$(CFLAGS)


%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc $(CFLAGS) -c $<

all: scmp scmpasm
	
scmp: scmp.o cmpstrlex.o
	gcc $(LDFLAGS) -o $@ $^

scmpasm: scmp.o cmpstrasmlex.o
	gcc $(LDFLAGS) -o $@ $^


clean:
	rm -f *.o *~
