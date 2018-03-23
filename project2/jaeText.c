#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
    int x, y;
}node;

int row, col;
int x ,y; 
FILE *fp;
WINDOW *topbar, *textbox, *bottombar, *textOuter;
struct node* array = NULL, *end = NULL;
int total = 0;

int main(int argc,char *argv[])
{  
  if(argc != 2){
  printf("Please provide a file to read: %s <a file name>\n", argv[0]);
  return(1);
  }
  fp = fopen(argv[1], "r");
  
  if(fp){
      char letter = '\0';
      int counter = 0;
      wmove(textbox, 0, 0);
      while(fscanf(fp, "%c", &letter) != EOF){
          getyx(textbox, y, x);
          total++;
          if(array == NULL){
              array = (struct node*)malloc(sizeof(node));
              array->c = letter;
              array->id = counter;
              array->nextNode = NULL;
              array->x = x;
              array->y = y;
              end = array;
          }
          else{
              end->nextNode = (struct node*)malloc(sizeof(node)); 
              end->nextNode->c = letter;
              end->nextNode->id = counter;
              end->nextNode->nextNode = NULL;
              end->x = x;
              end->y = y;
              end = end->nextNode;
          }
      }

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
      mvwprintw(bottombar, 0, 1, "Click Q to quit - row 0 | col 0");
      wrefresh(bottombar);
    
      textbox = newwin(row-5, col-2, 2, 1);

      struct node *tmp = array;
      int first = 1;
  		while(tmp != NULL){      	        
            wprintw(textbox, "%c", tmp->c);
      		tmp = tmp->nextNode;
  		}
        wrefresh(textbox);
        wrefresh(textOuter);
        wrefresh(textbox); 

        int c, quit = -1;
        wmove(textbox, 0, 0);
        wrefresh(textbox);
        int write = -1;
        while(quit == -1){
            getyx(textbox, y, x);
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
                        mvwprintw(bottombar, 1, 1, "insert mode");
                        break;
                    case 'i':
                        write = 0;
                        mvwprintw(bottombar, 1, 1, "insert mode");
                        break;
                    case '\033':
                        getch();
                        switch(getch()){
                            case 'A'://arrow up
                                if(y > 0){
                                    wmove(textbox, y-1, x);
                                    y = y-1;
                                    x = x;
                                }
                                wrefresh(textbox);
                                break;
                            case 'B'://arrow down
                                if(row-3 > y){
                                    wmove(textbox, y+1, x);
                                    y = y+1;
                                    x = x;
                                }
                                wrefresh(textbox);
                                break;
                            case 'C'://arrow right
                                if(col > x){
                                    wmove(textbox, y, x+1);
                                    y = y;
                                    x = x+1;
                                }
                                wrefresh(textbox);
                                break;
                            case 'D'://arrow left
                                if(x > 0){
                                    wmove(textbox, y, x-1);
                                    y = y;
                                    x = x-1;
                                }
                                wrefresh(textbox); 
                                break;
                        }        
                        break;
                    default:
                        wprintw(textbox, "You clicked %c", (char)c);
                        wrefresh(textbox);
                        wrefresh(textOuter);
                        break;
                }
            }
            else{
                switch(c){
                    case '\033':
                        getch();
                        switch(getch()){
                            case 'A'://arrow up
                                if(y > 0){
                                    wmove(textbox, y-1, x);
                                    y = y-1;
                                    x = x;
                                }
                                wrefresh(textbox);
                                break;
                            case 'B'://arrow down
                                if(row-3 > y){
                                    wmove(textbox, y+1, x);
                                    y = y+1;
                                    x = x;
                                }
                                wrefresh(textbox);
                                break;
                            case 'C'://arrow right
                                if(col > x){
                                    wmove(textbox, y, x+1);
                                    y = y;
                                    x = x+1;
                                }
                                wrefresh(textbox);
                                break;
                            case 'D'://arrow left
                                if(x > 0){
                                    wmove(textbox, y, x-1);
                                    y = y;
                                    x = x-1;
                                }
                                wrefresh(textbox); 
                                break;
                        }        
                        break;
                    default:
                        wprintw(textbox, "testtest1");
                        struct node *tmp = array;
                        for(int i=0; i<total;i++){
                            if(tmp->x == x && tmp->y == y){
                               struct node *holder = tmp->nextNode;
                               tmp->nextNode = (struct node*)malloc(sizeof(node));
                               tmp->nextNode->c = c;
                               tmp->nextNode->id = tmp->id + 1;
                               tmp->nextNode->x = x;
                               tmp->nextNode->y = y;
                               tmp->nextNode->nextNode = holder;
                            }
                            else{
                                tmp = tmp->nextNode;
                            }
                        }
                        wprintw(textbox, "testtest2");

                        tmp = array;
                        wmove(textbox, 0, 0);
                        while(tmp != NULL){
                            wprintw(textbox, "%c", tmp->c); 
                        }
                        wrefresh(textbox);
                        break;
                }
            }
            mvwprintw(bottombar, 0, 1, "Click Q to quit - row %d | col %d",y, x);
            wrefresh(bottombar);
            wmove(textbox, y, x);
            wrefresh(textbox);
        }
  }
  else{
      //bad filename
  }

  endwin();
  fclose(fp);
  return(0);
}
