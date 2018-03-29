#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "main.h"
#include "searchreplace.h"


void searchreplace(int x, int y){
mvwprintw(bottombar, 1, 1, "\n");
mvwprintw(bottombar, 1, 1, "Enter text to search for:");
wrefresh(bottombar);

char * search = "";
int holdup = 0;
int wordLength = 0, searchLength = 0;
int cont = 0;
while(cont == 0){
    
    int c = getch();
    switch(c){
        case 10:
            cont = -1;
            break;
        default:
            wprintw(bottombar, "%c", c);
            wrefresh(bottombar);
            
            char *tmpsearch = (char *)malloc(strlen(search) + 1 + 1);
            
           
            for(int d = 0; d<strlen(search);d++){
                tmpsearch[d] = search[d];
            }

            tmpsearch[strlen(search)] = (char)c;
            tmpsearch[strlen(search) + 1] = '\0';
            
            search = tmpsearch;
            wordLength++;
            break; 
    }
}

mvwprintw(bottombar, 1, 1, "\n");
mvwprintw(bottombar, 1, 1, "Enter text to replace as:");
wrefresh(bottombar);

char *replace = "";

cont = 0;
while(cont == 0){
    int c = getch();
    switch(c){ 
        case 10:
            cont = -1;
            break;
        default:
            wprintw(bottombar, "%c", c);
            wrefresh(bottombar);
            
            char *tmpreplace = (char *)malloc(strlen(replace) + 1 +1);
            holdup = strlen(tmpreplace);

            for(int d = 0; d<strlen(replace);d++){
                tmpreplace[d] = replace[d];
            }
            
            tmpreplace[strlen(replace)] = (char)c;
            tmpreplace[strlen(replace) + 1] = '\0';
            
            replace = tmpreplace;
            searchLength++;
            break;
    }
}

mvwprintw(bottombar, 1, 1, "\n");
mvwprintw(bottombar, 1, 1, "Normal Mode");
wrefresh(bottombar);

int listlen = 0;

struct node *tmp = array;
while(tmp != NULL){
    listlen++;
    tmp = tmp->nextNode;
}



struct node *prev = NULL, *cur = NULL, *first = NULL, *word = NULL, *wtmp = NULL;

int i = 0;
int j = 0;

for(i = 0; i<searchLength; i++){
    if(word == NULL){
        word = (struct node*)malloc(sizeof(struct node));
        word->c = replace[i];
        word->nextNode = NULL;
        wtmp = word;
    }
    else{
        wtmp->nextNode = (struct node*)malloc(sizeof(struct node));
        wtmp = wtmp->nextNode;
        wtmp->c = replace[i];
        wtmp->nextNode = NULL;
    }
}


tmp = array;
for(i = 0; i < (listlen - wordLength); i++) {
    if(tmp->c == search[0]) {
        int same = 1;

        struct node *tmp2 = tmp;
        for(j=0; j < wordLength; j++) {
          if(tmp2->c != search[j]) {
            same = -1;
            break;
          }
          tmp2 = tmp2->nextNode;
        }
        if(same == 1) {
                struct node *holder = tmp2;
                cur = word;
                
                while(cur != NULL){
                    prev->nextNode = (struct node*)malloc(sizeof(struct node));
                    prev = prev->nextNode;
                    prev->c = cur->c;
                    prev->nextNode = NULL;
                    cur = cur->nextNode;
                }
                prev->nextNode = holder;
        }
  }
  prev = tmp;
  tmp = tmp->nextNode;
}

wmove(textbox, y, x);
wrefresh(textbox);

}

