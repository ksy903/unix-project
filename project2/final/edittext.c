#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include "edittext.h"

void insertChar(char input){
    tmp = array;
	struct node *prev;

	while(tmp != NULL){

		//printf("%d %d %d %d", tmp->myx, x, tmp->myy, y);
		if(tmp->myx == x && tmp->myy == y){
			//printf("in if of loop");
			struct node *holder = tmp;
			tmp = (struct node*)malloc(sizeof(node));
			tmp->c = input;
			tmp->id = prev->id + 1;
			tmp->nextNode = holder;
			//tmp->nextNode->myx = x+1;
			prev->nextNode = tmp;
			break;
		}

		prev = tmp;
		tmp = tmp->nextNode;
	} 
}

