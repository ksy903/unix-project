#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "addline.h"

void addline(int x, int y){
    struct node *tmp = array;

    while(tmp!=NULL){
        if(tmp->myy == y && tmp->myx == x){
            struct node *holder = tmp->nextNode;
            tmp->nextNode = (struct node*)malloc(sizeof(struct node));
            tmp->nextNode->c = '\n';
            tmp->nextNode->nextNode = holder;
            break;
        }
        tmp=tmp->nextNode;
    }
}
