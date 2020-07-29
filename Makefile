CC          =	gcc

CFLAGS      =	-Wall -std=c99 -pedantic -g  

prog: makebin src/*.c
	$(CC) $(CFLAGS) src/*.c -Iinclude -o bin/main

cppcheck:
	cppcheck --enable=all --language=c --std=c99 --inconclusive --suppress=missingInclude src/*.c -i ./include

doxy: makedocs Doxyfile
	doxygen

makebin: 
	mkdir -p bin

makedocs: 
	mkdir -p docs

clean:
	rm bin/*
