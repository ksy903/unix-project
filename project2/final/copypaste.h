#ifndef COPYPASTE
#define COPYPASTE

void copy(struct node *ary, WINDOW *textbox, int x, int y);
struct node* findNode(int ax, int ay);
void highlight(struct node *a, struct node *b);
void paste(int x, int y);
 
struct node *copyTxt;

#endif
