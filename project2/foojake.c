#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
}node;

void save(struct node* array, char *fileName, size_t nameLength); 


int main(int argc, char *argv[])
{
 
  
  int ch, prev, row, col;
  prev = EOF;
  FILE *fp;
  int c;

  if(argc != 2) {
    printf("Usage: %s <a c file name>\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");

  if(fp == NULL) {
    perror("Cannot open input file");
    exit(1);
  }

 struct node* array = NULL, *end = NULL;


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
      	//	printf("%c", tmp->c);
      		tmp = tmp->nextNode;
  		}
      size_t namelength = strlen(argv[1]); 
      save((void*)tmp, argv[1], namelength); 

      refresh(); 
      getch(); 
      endwin(); 
  }
  else{
      //bad filename
  } 
  fclose(fp);
 
  return(0);
}

void save(struct node* array, char *fileName, size_t nameLength) {
  FILE *fp;
  fp = fopen("fileName", "wb");     
  
  if(fp != NULL) {
    node *currentNode = array; 
    
    node *holdNext = NULL; 
    
    while (currentNode != NULL) {
      holdNext = currentNode->nextNode;
      currentNode->nextNode = NULL;

      fseek(fp, 0, SEEK_END); 
      fwrite(currentNode, sizeof(array), 1, fp); 
      
            
      printf("Saved"); 
    }
  fclose(fp); 

  }
  else {
    printf("Save Error: could not open file"); 

  }

  

}
