#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
    int myx, myy;
}node;

int row, col;
int x ,y; 
FILE *fp;
WINDOW *topbar, *textbox, *bottombar, *textOuter;
struct node* array = NULL, *end = NULL, *tmp = NULL;
int total = 0;

void copy(struct node *ary, WINDOW *textbox, int x, int y);
void findEdges(int ax, int ay, int bx, int by, struct node *start, struct node *end);
//int ax, int ay, struct node *start, struct node *end
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
      mvwprintw(bottombar, 0, 1, "Click Q to quit - row 0 | col 0");
      mvwprintw(bottombar, 1, 1, "Normal Mode");
      wrefresh(bottombar);
      char letter = '\0';
      int counter = 0;
      wmove(textbox, 0, 0);
      textbox = newwin(row-5, col-2, 2, 1);


      while(fscanf(fp, "%c", &letter) != EOF){
          total++;
          if(array == NULL){
              array = (struct node*)malloc(sizeof(node));
              array->c = letter;
              array->id = counter;
              array->nextNode = NULL;
              end = array;
          }
          else{
              end->nextNode = (struct node*)malloc(sizeof(node)); 
              end->nextNode->c = letter;
              end->nextNode->id = counter;
              end->nextNode->nextNode = NULL;
              end = end->nextNode;
          }
          wprintw(textbox, "%c", end->c);
          getyx(textbox, y, x);
          end->myx = x;
          end->myy = y;
      } 

        wrefresh(textOuter);
        wrefresh(textbox); 

        int c, quit = -1;
        wmove(textbox, 0, 0);
        wrefresh(textbox);
        int write = -1;
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
                        mvwprintw(bottombar, 1, 1, "Insert Mode");
                        break;
                    case 'i':
                        write = 0;
                        mvwprintw(bottombar, 1, 1, "Insert Mode");
                        break;
                    case 'z':
                        ;
                        int posX, posY;
                        getyx(textbox, posY, posX);
                        copy(array, textbox, posX, posY);
                        
                        break;
                    case 'Z':
                        ; 
                        getyx(textbox, posY, posX);
                        copy(array, textbox, posX, posY); 
                        break;
                    case 'y':

                        break;
                    case 'Y':

                        break;
                    case '\033':
                        getch();
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
                                break;
                        }
                        mvwprintw(bottombar, 0, 1, "Click Q to quit - row %d | col %d",y, x);
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
                        mvwprintw(bottombar, 0, 1, "Click Q to quit - row %d | col %d",y, x);
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
                        mvwprintw(bottombar, 0, 1, "Click Q to quit - row %d | col %d",y, x);
            wrefresh(bottombar);
            wmove(textbox, localcopyy, localcopyx);
            wrefresh(textbox);
                        wmove(textbox, localcopyy, localcopyx+1);
                        wrefresh(textbox);
                        break;
                       
                }
            }
            
        }
  }
  else{
      //bad filename
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

void copy(struct node *ary, WINDOW *textbox, int x, int y){
    int localcopyy = y, localcopyx = x;
    mvwprintw(bottombar, 1, 20, "Copy Mode - Use arrows to move, and 'c' to copy");
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
            break;
    }   
}

void findEdges(int ax, int ay, int bx, int by, struct node *start, struct node *end){
    struct node *tmp = array;
    while(tmp != NULL){
        if(tmp->myx = ax); 
    }
}
