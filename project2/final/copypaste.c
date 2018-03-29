#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "copypaste.h"


 void paste(int x, int y){
     struct node *tmp = array;
 
     while(tmp != NULL){
         if(tmp->myy == y && tmp->myx == x){
             struct node *holder = tmp->nextNode;
             struct node *copycopy = copyTxt;
 
             while(copycopy != NULL){
                 tmp->nextNode = (struct node *)malloc(sizeof(struct node));
                 tmp->nextNode->c = copycopy->c;
                 tmp->nextNode->nextNode = NULL;
                 tmp = tmp->nextNode;
                 copycopy = copycopy->nextNode;
             }
 
             tmp->nextNode = holder;
             break;
         }
         tmp = tmp->nextNode;
     }
 }
 
 void copy(struct node *ary, WINDOW *textbox, int x, int y){
     int localcopyy = y, localcopyx = x;
     struct node *start = NULL, *end = NULL;
     start = findNode(x, y);
     int repeat = 1;
     if(start != NULL){
 
         mvwprintw(bottombar, 1, 1, "Copy Mode - Use arrows to move, and 'c' to copy");
         wrefresh(bottombar);
         wmove(textbox, y, x);
         wrefresh(textbox);
 
         while(repeat == 1){
             getyx(textbox, y, x);
             localcopyy = y;
             localcopyx = x;
             switch(getch()){
                 case KEY_UP:
                        if(y > 0){
                                    localcopyy = localcopyy-1;
                                    localcopyx = localcopyx;
                                }
                      copyTxt = NULL;
                     end = findNode(localcopyx, localcopyy);
                     if(start != NULL && end != NULL){
                         highlight(start, end);
                     }
                     wmove(textbox, localcopyy, localcopyx);
                     wrefresh(textbox);
                     break;  
                case KEY_DOWN:
                        if(row-3 > y){
                                    localcopyy = localcopyy+1;
                                    localcopyx = localcopyx;
                                }
                       copyTxt = NULL;
                     end = findNode(localcopyx, localcopyy);
                     if(start != NULL && end != NULL){
                         highlight(start, end);
                     }
                     wmove(textbox, localcopyy, localcopyx);
                     wrefresh(textbox);
                     break; 
                case KEY_LEFT:
                        if(x > 0){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx-1;
                                }
                      copyTxt = NULL;
                     end = findNode(localcopyx, localcopyy);
                     if(start != NULL && end != NULL){
                         highlight(start, end);
                     }
                     wmove(textbox, localcopyy, localcopyx);
                     wrefresh(textbox);
                     break;          
                case KEY_RIGHT:
                        if(col > x){
                                    localcopyy = localcopyy;
                                    localcopyx = localcopyx+1;
                                }
                                
                     copyTxt = NULL;
                     end = findNode(localcopyx, localcopyy);
                     if(start != NULL && end != NULL){
                         highlight(start, end);
                     }
                     wmove(textbox, localcopyy, localcopyx);
                     wrefresh(textbox);
                     break;
                 case 'c':
                     ;
                     struct node *cpy = copyTxt;
                     wmove(bottombar, 1, 1);
                     while(cpy != NULL){
                         wprintw(bottombar, "%c", cpy->c);
                         cpy = cpy->nextNode;
                     }
                     wrefresh(bottombar);
 
                     repeat = -1;
                     break;
                 case 'C':
                     repeat = -1;
                     break;
                 default:
                     break;
             }
         }
     }
 }
 
 struct node* findNode(int ax, int ay){
     struct node *tmp = array;
     while(tmp != NULL){
         if(tmp->myx == ax && tmp->myy == ay){
             break;
         }
         tmp = tmp->nextNode;
     }
 
     if(tmp != NULL){
         struct node *find = (struct node*)malloc(sizeof(struct node));
         find->c = tmp->c;
         find->id = tmp->id;
         find->nextNode = tmp->nextNode;
         find->myy = tmp->myy;
         find->myx = tmp->myx;
         return find;
     }
     else{
         return NULL;
     }
 }
 
 void highlight(struct node *a, struct node *b){
     struct node *tmp = array;
     int found = -2;
     wclear(textbox);
     wrefresh(textbox);
 
     wmove(textbox, 0, 0);
     struct node *tmp2 = NULL;
     while(tmp != NULL){
         if(tmp->myy == a->myy && tmp->myx == a->myx || tmp->myy == b->myy && tmp->myx == b->myx){
             found++;
         }
 
         if(found != -2 && found < 0){
             wattron(textbox, A_STANDOUT);
             if(tmp2 == NULL){
                 copyTxt = (struct node*)malloc(sizeof(struct node));
                 copyTxt->c = tmp->c;
                 copyTxt->nextNode = NULL;
                 tmp2 = copyTxt;
             }
             else{
                 tmp2->nextNode = (struct node*)malloc(sizeof(struct node));
                 tmp2->nextNode->c = tmp->c;
                 tmp2->nextNode->nextNode = NULL;
                 tmp2 = tmp2->nextNode;
             }
         }
         else{
             wattroff(textbox, A_STANDOUT);
         }
 
         if(found == 0){
             tmp2->nextNode = (struct node*)malloc(sizeof(struct node));
             tmp2->nextNode->c = tmp->c;
             tmp2->nextNode->nextNode = NULL;
             tmp2 = tmp2->nextNode;
             found++;
         }
 
         wprintw(textbox, "%c", tmp->c);
         tmp = tmp->nextNode;
     }
     wrefresh(textbox);
 }

