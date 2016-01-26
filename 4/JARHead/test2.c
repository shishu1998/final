#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

static void clean_up_memory(int signo) {
}

int main(int argc, char** argv) {

  int c;

  initscr();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  while (1) {
    c = getch();
    if (c != -1) {
      printw("%d", c);
    }
    refresh();
  }

  return 0;
}
