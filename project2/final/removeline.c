#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "removeline.h"

void removeLine(WINDOW *textbox, int y, int x,struct node* array){
 
   struct node* tmp = array;
   struct node* tmp2 = tmp;
   struct node* prev = tmp;
   struct node* after = tmp;
   while(tmp != NULL){
    if(tmp->myy == y){
      tmp2 = tmp;
      while(tmp2 != NULL && tmp2->myy == y){
        if(tmp2->nextNode == NULL){
           after=tmp2;
        }
        else{after=tmp2->nextNode;}
        tmp2=tmp2->nextNode;
      }
      //after=tmp2;
      break;
    }
    prev = tmp;
    tmp = tmp->nextNode;
   }
   if(prev->myx == array->myx && prev->myy == array->myy){
    array->c = after->c;
    array->nextNode = after->nextNode;
   }
   else{
     prev->nextNode = after;
   }
   //here
   //prev->nextNode = after;
   array = array->nextNode;
   //here
   wmove(textbox, 0, 0);
   wclear(textbox);
   wrefresh(textbox);
   wmove(textbox, 0, 0);
   tmp = array;
   int tmpx, tmpy;
   while(tmp!=NULL){
     
     getyx(textbox, tmpy, tmpx);
     wprintw(textbox, "%c", tmp->c);
     tmp->myy = tmpy;
     tmp->myx = tmpx;
     tmp=tmp->nextNode;
   }
   wmove(textbox,y,x);
 
 }
