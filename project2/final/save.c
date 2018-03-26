 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include "main.h"
 #include "save.h"

void save(struct node* array, char *fileName) {
   struct node *p = array;
   FILE *fp;
   fp = fopen(fileName, "w");
   while (p != NULL) {
       fprintf(fp, "%c", p->c);
       p = p->nextNode;
   }
   fclose(fp);
 }
