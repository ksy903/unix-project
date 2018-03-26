#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "readfile.h"

void readfile(FILE *fp){
    char letter = '\0';
    	while(fscanf(fp, "%c", &letter) != EOF){
          total++;
           if(array == NULL){
               array = (struct node*)malloc(sizeof(node));
               array->c = letter;
               array->id = total;
               array->nextNode = NULL;
               end = array;
           }
           else{
               end->nextNode = (struct node*)malloc(sizeof(node)); 
               end->nextNode->c = letter;
               end->nextNode->id = total;
               end->nextNode->nextNode = NULL;
               end = end->nextNode;
           }
           wprintw(textbox, "%c", end->c);
           getyx(textbox, y, x);
           end->myx = x;
           end->myy = y;
       }	
}
