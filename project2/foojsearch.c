#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
typedef struct node{
    char c;
    int id;
    struct node *nextNode;
}node;

node *createNode(char data, node *parent) {
    node *ptr=(node*)malloc(sizeof(node));
    if(ptr==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    if(parent!=NULL) parent->nextNode=ptr;
    ptr->c=data;
    ptr->nextNode=NULL;
    return ptr;
}


int main(int argc, char** argv)
{
  //initscr(); //creates stdscr
  //raw();

  //if(argc != 2) {
	//printf("Please provide the string to search for followed 
		//by the string to replace it with.\n");
  //}



  int listlen = 0;
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
              array->id = listlen;
              array->nextNode = NULL;
              end = array;
          }
          else{
              end->nextNode = (struct node*)malloc(sizeof(node)); 
              end->nextNode->c = letter;
              end->nextNode->id = listlen;
              end->nextNode->nextNode = NULL;
              end = end->nextNode;
          } listlen++;
      }
      struct node *tmp = array;
  		while(tmp != NULL){
      		printf("%c", tmp->c);
      		tmp = tmp->nextNode;
  		}
  }
  else{
      //bad filename
  }

struct node *tmp = array;
struct node *prev = array;
char str[] = "test";
char str2[] = "willywonka";
int wordLength = strlen(str);
int wordLength2 = strlen(str2);
struct node *wnode;
int i = 0;
int j = 0;

// Store the string to the list
    node *first=NULL, *cur=NULL;
    for(int i=0; i < wordLength2; i++) {
        cur=createNode(str2[i],cur);
        if(first==NULL) first=cur;
    }

    // Now print it out
    //printf("*************************************\n");
    //cur=first;
    //while(cur->nextNode!=NULL) {
    //  printf("%c\n", cur->c);
    //    cur=cur->nextNode;
    //}



for(i = 0; i < listlen - wordLength; i++) {
    if(tmp->c == str[0]) {
	int same = 1;
        //printf("\nWe found the letter we were searching for: %c\n", tmp->c);
	struct node *tmp2 =tmp;
	for(j=0; j < wordLength; j++) {
	  if(tmp2->c != str[j]) {
		same = -1;
		break;
	  }
	  tmp2 = tmp2->nextNode;  
	}
	if(same == 1) {
		printf("Word found at point: %d\n",tmp->id);
		printf("The letter at the point is: %c\n", tmp->c);
		prev->nextNode = first;
		cur->nextNode = tmp2;
		printf("This is the id pointed by prev: %d\n", prev->id);
    	}
  }
  prev = tmp;
  tmp = tmp->nextNode;
}

//print and free memory
tmp = array;
while(tmp != NULL) {
  prev = tmp;
  printf("%c", tmp->c);
  tmp = tmp->nextNode;
  free(prev);  
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
