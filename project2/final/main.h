#ifndef MAIN
#define MAIN

typedef struct node{
    char c;
    int id;
    struct node *nextNode;
    int myx, myy;
}node;
 
int row, col;
int x ,y;
FILE *fp;
WINDOW *topbar, *textbox, *bottombar, *textOuter;
struct node* array, *end, *tmp;
int total;
int posX, posY;
int write;

#endif
