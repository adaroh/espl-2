.PHONY: all clean
.SUFFIXES: .c .o .h .asm
CFLAGS=-g -m32 -O0 -Wall
LDFLAGS=$(CFLAGS)


%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc $(CFLAGS) -c $<

all: scmp scmpasm
	
scmp: scmp.o cmpstr.o
	gcc $(LDFLAGS) -o $@ $^

scmpasm: scmp.o cmpstrasm.o
	gcc $(LDFLAGS) -o $@ $^


clean:
	rm -f *.o *~
