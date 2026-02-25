COMPILER = gcc
OPT = -Wreturn-type -Wimplicit-function-declaration -pedantic

all: bit_decode1 bit_decode2

bit_decode1: bit_decode1.o
	$(COMPILER) bit_decode1.o -o bit_decode1

bit_decode1.o: bit_decode1.c
	$(COMPILER) $(OPT) -c bit_decode1.c -o bit_decode1.o

bit_decode2: bit_decode2.o
	$(COMPILER) bit_decode2.o -o bit_decode2

bit_decode2.o: bit_decode2.c
	$(COMPILER) $(OPT) -c bit_decode2.c -o bit_decode2.o

lab2.zip: Makefile bit_decode1.c bit_decode2.c
	zip lab2.zip Makefile bit_decode1.c bit_decode2.c

clean:
	rm -rf *.o bit_decode1 bit_decode2 lab2.zip
