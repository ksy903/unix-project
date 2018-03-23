#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
}node;

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
              end->c = letter;
              end->id = counter;
              end->nextNode->nextNode = NULL;
              end = end->nextNode;
          }
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

  struct node *tmp = array;
  while(tmp != NULL){
      printf("%c", tmp->c);
      tmp = tmp->nextNode;
  }

  return(0);
}
