#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
}node;

void copy(struct node* ary, WINDOW *win); 

int main()
{
  //initscr(); //creates stdscr
  //raw();
  
  FILE *fp;
  
  struct node* array = NULL, *end = NULL;

  fp = fopen("foo.txt", "r");

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
      struct node *tmp = array;
  		while(tmp != NULL){
      		printf("%c", tmp->c);
      		tmp = tmp->nextNode;
  		}

        int c = -1;
        while(1==1){
            c = getch();
            //if(c!=-1)copy();
        }

  }
  else{
      //bad filename
  }

  /*
  initscr();
  raw();
  fgets(str, 60, fp);
  printw(str);
  fgets(str, 60, fp);
  printw(str);
  fclose(fp);
  getch();
  endwin();
  */

  

  return(0);
}

void copy(struct node* ary, WINDOW *win){
    int x, y;
    getyx(win, y, x);
    printf("%d %d\n", y, x);
}

