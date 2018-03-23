#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
}node;

int main(int argc,char *argv[])
{
  
  //raw();
  int row, col;
  int x ,y; 
  FILE *fp;
  
  struct node* array = NULL, *end = NULL;
  
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
      struct node *tmp = array;
  		while(tmp != NULL){      	        
		printw("%c", tmp->c);
      		tmp = tmp->nextNode;
  		}
  refresh();
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
