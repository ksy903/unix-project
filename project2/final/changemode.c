#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "changemode.h"
#include "save.h"

void toNormal(){
    write = -1;

    mvwprintw(bottombar, 1, 1, "\n");
    mvwprintw(bottombar, 1, 1, "Normal Mode");
    wrefresh(bottombar);
}

void toWrite(){
    write = 1;

    mvwprintw(bottombar, 1, 1, "\n");
    mvwprintw(bottombar, 1, 1, "Insert Mode");
    wrefresh(bottombar);
}

void toCommand(struct node* array,char *argv[]){
 
     int i = 0;
     char command[2];
     while((command[i] = getch()) != '\n'){
       if(command[i] == '\033')
       {
         mvwprintw(bottombar,1,1, "\n");
         mvwprintw(bottombar,1,1, "Normal mode");
         wrefresh(bottombar);
         return;
       }
       wprintw(bottombar,"%c",command[i]);
       wrefresh(bottombar);
       i++;
     }
 
     if(command[0] == 'w' && command[1] == 'q')
     {
         save(array,argv[1]);
         endwin();
         exit(0);
     }
     else if(command[0] == 'w')
     {
         save(array,argv[1]);
         mvwprintw(bottombar,1,1, "\n");
                 mvwprintw(bottombar,1,1, "Normal mode");
                 wrefresh(bottombar);
                 return;
     }
     else if(command[0] == 'q')
     {
         endwin();
         exit(0);
     }
 /*
     char c;
     c = getch();
     switch(c){
         case 'w':
         wprintw(bottombar,"w");
         wrefresh(bottombar);
         break;
         case 'q':
         wprintw(bottombar, "q");
         wrefresh(bottombar);
         break;
 }
 */
 };

