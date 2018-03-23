all: foo

foo: foo.o foojae.o
	gcc -o foo foo.o -lncurses
	gcc -o foojae foojae.o -lncurses

foo.o: foo.c 
	gcc -c foo.c -lncurses

foojae.o: foojae.c
	gcc -c foojae.c -lncurses

clean: 
	rm foo *.o
