%.o: %.c
	gcc -c -o $@ $<

all: canalyze

clean:
	rm -f *.o
 
canalyze: canalyze.o fgetname.o namelist.o
	cc -o $@ $^
 
canalyze.o: canalyze.c fgetname.h namelist.h
fgetname.o: fgetname.c fgetname.h
namelist.o: namelist.c namelist.h