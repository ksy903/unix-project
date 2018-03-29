#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "copypaste.h"
#include "save.h"
#include "removeline.h"
#include "readfile.h"
#include "changemode.h"
#include "edittext.h"
#include "addline.h"
#include "commandmode.h"
#include "searchreplace.h"

int main(int argc,char *argv[])
{ 
  if(argc != 2){
  printf("Please provide a file to read: %s <a file name>\n", argv[0]);
  return(1);
  }
  fp = fopen(argv[1], "r");

  if(fp){
      initscr();
      noecho();
      refresh();
      getmaxyx(stdscr, row, col);
      topbar = newwin(1, col, 0, 0);
      //box(topbar, 0, 0);
      mvwprintw(topbar, 0, 1, "Group 6 | %s", argv[1]);
      wrefresh(topbar);
      textOuter = newwin(row-3, col, 1, 0);
      box(textOuter, 0, 0);
      wrefresh(textOuter);
      bottombar = newwin(2, col, row-2, 0);
      mvwprintw(bottombar, 0, 1, "Press Q to quit | S to save | Z to copy | Y to paste | I to insert | F to search | : for command mode ");
      mvwprintw(bottombar, 0, col-15, "row 0 | col 0"); 
      mvwprintw(bottombar, 1, 1, "Normal Mode");
      wrefresh(bottombar);
      char letter = '\0';
      int counter = 0;
      wmove(textbox, 0, 0);
      textbox = newwin(row-5, col-2, 2, 1);
 
      readfile(fp);
    

        wrefresh(textOuter);
        wrefresh(textbox); 

        int c, quit = -1;
        wmove(textbox, 0, 0);
        wrefresh(textbox);
        write = -1;
        while(quit == -1){
            getyx(textbox, y, x);
            int localcopyx = x, localcopyy = y;
            c = getch();
            if(write == -1){
                switch(c){
                    case 'Q':
                        endwin();
                        quit = 1;
                        break;
                    case 'q':
                        endwin();
                        quit = 1;
                        break;
                    case 'I':
                        write = 0;
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Insert Mode");
                        wrefresh(bottombar); 
                        break;
                    case 'i':
                        write = 0;
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Insert Mode");
                        wrefresh(bottombar); 
                        break;
                    case 'z':
                        getyx(textbox, posY, posX);
                        copy(array, textbox, posX, posY);
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Copied"); 
                        //mvwprintw(bottombar, 1, 1, "\n");
                        wrefresh(bottombar);
                        break;
                    case 'Z':
                        getyx(textbox, posY, posX);
                        copy(array, textbox, posX, posY);
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Copied"); 
                        //mvwprintw(bottombar, 1, 1, "\n");
                        wrefresh(bottombar);
                        break;
                    case 'y':
                        getyx(textbox, posY, posX);
                        paste(posX, posY);
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Pasted"); 
                        wrefresh(bottombar);
			wrefresh(textbox); 
                        break;
                    case 'Y':
                        getyx(textbox, posY, posX);
                        paste(posX, posY);
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Pasted"); 
                        wrefresh(bottombar); 
                        break;
                    case 's':
                        save(array, argv[1]); 
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Saved"); 
                        wrefresh(bottombar); 
                        break;
                    case 'S':
                        save(array, argv[1]); 
                        mvwprintw(bottombar, 1, 1, "\n"); 
                        mvwprintw(bottombar, 1, 1, "Saved"); 
                        wrefresh(bottombar); 
                        break;
		    case ':':
			mvwprintw(bottombar,1,1, "\n");
			mvwprintw(bottombar,1,1, "Command Mode: ");
			wrefresh(bottombar);
			toCommand(array, argv);
			break;
                    case '\033':
                        getch();
                        switch(getch()){
                            case 'A'://arrow up
                                if(y > 0){
                                    localcopyy = localcopyy-1;
                                    localcopyx = localcopyx;
                                }
                                break;
                            case 'B'://arrow down
                                if(row-3 > y){
                                    localcopyy = localcopyy+1;
                                    localcopyx = localcopyx;
                                }
                                break;
                            case 'C'://arrow right
                                if(col > x){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx+1;
                                }
                                break;
                            case 'D'://arrow left
                                if(x > 0){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx-1;
                                }
                                break;
                            default: 
                                break;
                        }
                        mvwprintw(bottombar, 0, 1, "Press Q to quit | S to save | Z to copy | Y to paste | I to insert | F to search | : for command mode ");
                        mvwprintw(bottombar, 0, col - 18, "row %d | col %d0", localcopyy, localcopyx); 
                        wrefresh(bottombar);
                        wmove(textbox, localcopyy, localcopyx);
                        wrefresh(textbox);
                        break;
                }
            }
            else{
                switch(c){
                    case '\033': 
                        nodelay(stdscr, TRUE);
                        int a = getch();
                        //mvwprintw(bottombar, 1, 15, "pressed:: %d", a);
                        if(a == 27){
                            mvwprintw(bottombar, 1, 1, "\n"); 
                            mvwprintw(bottombar, 1, 1, "Normal Mode");
                            wrefresh(bottombar);
                            write = -1;
                            break;
                        }
                        nodelay(stdscr, FALSE);
                        switch(getch()){
                            case 'A'://arrow up
                                if(y > 0){
                                    wmove(textbox, localcopyy-1, localcopyx);
                                    localcopyy = localcopyy-1;
                                    localcopyx = localcopyx;
                                }
                                wrefresh(textbox);
                                break;
                            case 'B'://arrow down
                                if(row-3 > y){
                                    wmove(textbox, localcopyy+1, localcopyx);
                                    localcopyy = localcopyy+1;
                                    localcopyx = localcopyx;
                                }
                                wrefresh(textbox);
                                break;
                            case 'C'://arrow right
                                if(col > x){
                                    wmove(textbox, localcopyy, localcopyx+1);
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx+1;
                                }
                                wrefresh(textbox);
                                break;
                            case 'D'://arrow left
                                if(x > 0){
                                    wmove(textbox, localcopyy, localcopyx-1);
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx-1;
                                }
                                wrefresh(textbox); 
                                break;
                            default:
                                mvwprintw(bottombar, 1, 1, "Normal Mode");
                                wrefresh(bottombar);
                                write = -1;
                                break;
                        }
                        mvwprintw(bottombar, 0, 1, "Press Q to quit | S to save | Z to copy | Y to paste | I to insert | F to search | : for command mode ");
                        mvwprintw(bottombar, 0, col-18, "row %d | col %d", y,x); 
                        wrefresh(bottombar);
                        wmove(textbox, localcopyy, localcopyx);
                        wrefresh(textbox);
                        break;
                    default:
                        
                        
                        tmp = array;
                        struct node *prev;
                        
                        while(tmp != NULL){
                            
                            //printf("%d %d %d %d", tmp->myx, x, tmp->myy, y);
                            if(tmp->myx == x && tmp->myy == y){
                               //printf("in if of loop");
                               struct node *holder = tmp;
                               tmp = (struct node*)malloc(sizeof(node));
                               tmp->c = c;
                               tmp->id = prev->id + 1;
                               tmp->nextNode = holder;
                               //tmp->nextNode->myx = x+1;
                               prev->nextNode = tmp;
                               break;
                            }
                            
                            prev = tmp;
                            tmp = tmp->nextNode;
                        }

                        
 
                        tmp = array;
                        wclear(textbox);
                        wrefresh(textbox);
                        wmove(textbox, 0, 0);
                        while(tmp != NULL){
                            getyx(textbox, y, x);
                            wprintw(textbox, "%c", tmp->c); 
                            tmp->myy = y;
                            tmp->myx = x;
                            tmp = tmp->nextNode;
                        }
                        mvwprintw(bottombar, 0, 1, "Press Q to quit | S to save | Z to copy | Y to paste | I to insert | F to search | : to get back to command mode ");
                        mvwprintw(bottombar, 0, col-18, "row %d | col %d", y,x); 
                        wrefresh(bottombar);
                        wmove(textbox, localcopyy, localcopyx);
                        wrefresh(textbox);
                        wmove(textbox, localcopyy, localcopyx+1);
                        wrefresh(textbox);
                        break;
                       
                }
            }
            struct node *tmp = array;
            wclear(textbox);
            wrefresh(textbox);
            wmove(textbox, 0, 0);
            int tmpy, tmpx, tmpi = 0;
            while(tmp!=NULL){
                getyx(textbox, tmpy, tmpx);
                wprintw(textbox, "%c", tmp->c);
                tmp->id = tmpi;
                tmp->myy = tmpy;
                tmp->myx = tmpx;
                tmpi++;
                tmp = tmp->nextNode;
            }
            wmove(textbox, localcopyy, localcopyx);
            wrefresh(textbox);
        } 
  }
  else{
      //bad filename
      printf("Bad File Name\n");
      return(1);
  }

  endwin();
  fclose(fp);

  tmp = array;
  while(tmp != NULL){
      printf("%c", tmp->c);
      tmp = tmp->nextNode;
  }

  return(0);
}


