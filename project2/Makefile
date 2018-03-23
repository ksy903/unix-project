all: foo

foo: foo.o
	gcc -o foo foo.o -lncurses

foo.o: foo.c 
	gcc -c foo.c -lncurses

clean: 
	rm foo *.o
