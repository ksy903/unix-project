#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "changemode.h"

void toNormal(){
    write = -1;

    mvwprintw(bottombar, 0, 1, "\n");
    mvwprintw(bottombar, 0, 1, "Normal Mode");
}

void toWrite(){
    write = 1;

    mvwprintw(bottombar, 0, 1, "\n");
    mvwprintw(bottombar, 0, 1, "Insert Mode");
}
