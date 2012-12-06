%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

EXECS=bsplitasm bmerge

all: clean $(EXECS)

bsplit: bsplit.o
	gcc -m32 -Wall -o bsplit bsplit.c

bmerge: bmerge.o
	gcc -m32 -Wall -o bmerge bmerge.c

bsplitasm: bsplitasm.o
	gcc -m32 -Wall -o $@ $^


distclean: clean
	rm -f bsplit bmerge bsplitasm


clean:
	rm -f *.o $(EXECS)
