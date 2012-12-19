%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.man: %.1
	nroff -man $< > $@

all: bpsplit bsplit bmerge bsplit.man bmerge.man

bpsplit: bpsplit.o
	$(CC) $(LDFLAGS) -o $@ $^

bsplit: bsplit.o
	$(CC) $(LDFLAGS) -o $@ $^

bmerge: bmerge.o #xsum.o
	$(CC) $(LDFLAGS) -o $@ $^

bsplit.o: bsplit.c xsum.h
bmerge.o: bmerge.c xsum.h
xsum.o: xsum.c xsum.h

clean:
	rm -f *.o 

distclean: clean
	rm -f bsplit bmerge
