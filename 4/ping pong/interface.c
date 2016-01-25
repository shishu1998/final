
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>

#include "interface.h"

#define DELAY 30000

int main() {
  setup();
}

void setup() {

  initscr();
  noecho();
  curs_set(FALSE);

/* ENVIRONMENT VARIABLES */

  // Scale the Environment to a square
  int max_y = 0, max_x = 0;
  getmaxyx(stdscr, max_y, max_x);
  int distance = 0;
  if(max_y > max_x) {
    distance = max_x;
  } else {
    distance = max_y;
  }
  int min_border_y = (max_y-distance)/2;
  int max_border_y = max_y - (max_y-distance)/2;
  int min_border_x = (max_x-(2* distance))/2;
  int max_border_x = max_x - (max_x-distance)/2;

  WINDOW *env = newwin(distance, 2 * distance, min_border_y, min_border_x);

  // Game Objects
  int paddle_length = distance * (1/8);

  // Points
  int myNumber = 0; // Which player are you?
  int points1 = 0; // Your points
  int points2 = 0; // Other's points

/* SETTING UP THE ENVIRONMENT */
  while(1) {
    wclear(env);
    draw_borders(env);
    wrefresh(env);
  }

  delwin(env);
  endwin();
}

void draw_borders(WINDOW *w) {
  int x, y, i;
  getmaxyx(w, y, x);
  for(i = 1; i < (y - 1); i++) {
    mvwprintw(w, i, 0, "|");
    mvwprintw(w, i, x - 1, "|");
  }
  for(i = 1; i < (x - 1); i++) {
    mvwprintw(w, 0, i, "-");
    mvwprintw(w, y - 1, i, "-");
  }
  mvwprintw(w, 0, 0, "+");
  mvwprintw(w, y - 1, 0, "+");
  mvwprintw(w, 0, x - 1, "+");
  mvwprintw(w, y - 1, x - 1, "+");
}
