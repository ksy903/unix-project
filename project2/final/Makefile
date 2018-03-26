CFILES = main.c addline.c changemode.c copypaste.c edittext.c readfile.c removeline.c save.c searchreplace.c
OFILES = main.o addline.o changemode.o copypaste.o edittext.o readfile.o removeline.o save.o searchreplace.o
HFILES = main.h addline.h changemode.h copypaste.h edittext.h readfile.h removeline.h save.h searchreplace.h
NAME = proj2_group6

all: $(NAME)	
$(NAME): $(OFILES) 
	gcc -o $(NAME) $(OFILES) -lncurses 
main.o: main.c
	gcc -c main.c -lncurses
addline.o: addline.c
	gcc -c addline.c -lncurses
changemode.o: changemode.c
	gcc -c changemode.c -lncurses
copypaste.o: copypaste.c
	gcc -c copypaste.c -lncurses
edittext.o: edittext.c
	gcc -c edittext.c -lncurses
readfile.o: readfile.c
	gcc -c readfile.c -lncurses
removeline.o: removeline.c
	gcc -c removeline.c -lncurses
save.o: save.c
	gcc -c save.c -lncurses
searchreplace.o: searchreplace.c
	gcc -c searchreplace.c -lncurses

.PHONY: clean
clean: 
	rm $(NAME)  *.o
