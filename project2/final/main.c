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
      cbreak();
      keypad(stdscr, TRUE);
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
      mvwprintw(bottombar, 0, 1, "Click Q to quit - row 0 | col 0");
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
            nodelay(textbox, false);
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
                        toWrite(); 
                        break;
                    case 'i':
                        toWrite(); 
                        break;
                    case 'R':
                        getyx(textbox, posY, posX);
                        searchreplace(posX, posY);
                        break;
                    case 'r':
                        getyx(textbox, posY, posX);
                        searchreplace(posX, posY);
                        break;
                    case 'z':
                        getyx(textbox, posY, posX);
                        copy(array, textbox, posX, posY);
                        //mvwprintw(bottombar, 1, 1, "\n");
                        wrefresh(bottombar);
                        break;
                    case 'Z':
                        getyx(textbox, posY, posX);
                        copy(array, textbox, posX, posY);
                        //mvwprintw(bottombar, 1, 1, "\n");
                        wrefresh(bottombar);
                        break;
		    case 'd':
			removeLine(textbox, y, x, array);
		        break;
                    case 'D':
			removeLine(textbox, y, x, array);
                        break;
                    case 'a':
			getyx(textbox, posY, posX);
			addline(posX,posY);
		        break;
                    case 'A':
			getyx(textbox, posY, posX);
			addline(posX,posY);
                        break;
                    case 'y':
                        getyx(textbox, posY, posX);
                        paste(posX, posY);
                        break;
                    case 'Y':
                        getyx(textbox, posY, posX);
                        paste(posX, posY);
                        break;
                    case KEY_UP:
                        if(y > 0){
                                    localcopyy = localcopyy-1;
                                    localcopyx = localcopyx;
                                }
                        break;
                case KEY_DOWN:
                        if(row-3 > y){
                                    localcopyy = localcopyy+1;
                                    localcopyx = localcopyx;
                                }
                        break;
                case KEY_LEFT:
                        if(x > 0){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx-1;
                                }
                                break;
                case KEY_RIGHT:
                        if(col > x){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx+1;
                                }
                                break;

                
                }
            }
            else{
                switch(c){
                case KEY_UP:
                        if(y > 0){
                                    localcopyy = localcopyy-1;
                                    localcopyx = localcopyx;
                                }
                        break;
                case KEY_DOWN:
                        if(row-3 > y){
                                    localcopyy = localcopyy+1;
                                    localcopyx = localcopyx;
                                }
                        break;
                case KEY_LEFT:
                        if(x > 0){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx-1;
                                }
                                break;
                case KEY_RIGHT:
                        if(col > x){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx+1;
                                }
                                break;


                    case KEY_BACKSPACE: 
                                               
                        tmp = array;
                        struct node *prev = NULL;
                            while(tmp != NULL){
                                if(tmp->myy == localcopyy && tmp->myx == localcopyx){
                                    prev->nextNode = tmp->nextNode;
                                    free(tmp);
                                    break;
                                }
                                prev = tmp;
                                tmp = tmp->nextNode;
                            }
                       localcopyx--; 
                        
                        break;

            case 27:
                             nodelay(textbox, true);
                   toNormal(); 
                        wmove(textbox, localcopyy, localcopyx);
                     
                        
                        //   getch();
                        //wechochar(textbox, '\0'); 
                        break;

            default:    
                        tmp = array;
                        
                       insertChar(c); 
                       
                        localcopyx++;
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
            mvwprintw(bottombar, 0, 1, "Click Q to quit - row %d | col %d", localcopyy, localcopyx);
                wrefresh(bottombar);
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


