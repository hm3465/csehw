COMPILER = gcc
OPT = -Wreturn-type -Wimplicit-function-declaration -pedantic

all: bit_decode1 bit_decode2

bit_decode1: bit_decode1.o
	$(COMPILER) bit_decode1.o -o bit_decode1

bit_decode1.o: bit_decode.c
	$(COMPILER) $(OPT) -DPROMPT -c bit_decode.c -o bit_decode1.o

bit_decode2: bit_decode2.o
	$(COMPILER) bit_decode2.o -o bit_decode2

bit_decode2.o: bit_decode.c
	$(COMPILER) $(OPT) -c bit_decode.c -o bit_decode2.o

lab2.zip: Makefile bit_decode.c
	zip lab2.zip Makefile bit_decode.c

clean:
	rm -rf *.o bit_decode1 bit_decode2 lab2.zip
