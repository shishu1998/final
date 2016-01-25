#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

void move(int y){
  int ch = getch();
  switch (ch) {
    case KEY_UP:
      y--;
    case KEY_DOWN:
      y++;
  }
}
