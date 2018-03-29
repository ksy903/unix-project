#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "readfile.h"

void readfile(FILE *fp){


//    scrollok(textbox, true);
    keypad(textbox, true);
    char letter = '\0';
    	while(fscanf(fp, "%c", &letter) != EOF){
          total++;
//	  scrollok(textbox,true);
//	  wrefresh(textbox);
           if(array == NULL){
               array = (struct node*)malloc(sizeof(node));
               array->c = letter;
               array->id = total;
               array->nextNode = NULL;
               end = array;
//	       scrollok(textbox,true);
//	       wrefresh(textbox);
           }
           else{
               end->nextNode = (struct node*)malloc(sizeof(node)); 
               end->nextNode->c = letter;
               end->nextNode->id = total;
               end->nextNode->nextNode = NULL;
               end = end->nextNode;
//	       scrollok(textbox,true);
  //             wrefresh(textbox);
           }
//	   scrollok(textbox,true);
//	   wrefresh(textbox);
           wprintw(textbox, "%c", end->c);
           getyx(textbox, y, x);
           end->myx = x;
           end->myy = y;
       }	
}
