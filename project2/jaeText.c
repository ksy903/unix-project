#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
}node;

int row, col;
int x ,y; 
FILE *fp;
WINDOW *topbar, *textbox, *bottombar, *textOuter;
struct node* array = NULL, *end = NULL;


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
      while(fscanf(fp, "%c", &letter) != EOF){ 
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
      }

      initscr();
      refresh();
      getmaxyx(stdscr, row, col);
      topbar = newwin(1, col, 0, 0);
      //box(topbar, 0, 0);
      mvwprintw(topbar, 0, 1, "Group 6 | %s", argv[1]);
      wrefresh(topbar);
      textOuter = newwin(row-3, col, 1, 0);
      box(textOuter, 0, 0);
      wrefresh(textOuter);
    
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
  
  getch();
  endwin();
  }
  else{
      //bad filename
  }

  endwin();
  fclose(fp);
  return(0);
}
