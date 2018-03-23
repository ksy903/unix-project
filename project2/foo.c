#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main()
{
  initscr(); //creates stdscr
  raw();
  
  FILE *fp;
  char str[60];

  fp = fopen("textfile.txt", "r");
  fgets(str, 60, fp);
  printw(str);
  fgets(str, 60, fp);
  printw(str);
  fclose(fp);
  getch();
  endwin();
  return(0);
}
