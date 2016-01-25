
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>

#define DELAY 30000

int main(int argc, char *argv[]) {

  initscr();
  noecho();
  curs_set(FALSE);

  //environment variables
  int max_y = 0, max_x = 0;
  getmaxyx(stdscr, max_y, max_x); // size of the terminal
  int paddle_length = (max_y - 3) * (1/8); // how long the paddles are
  int distance = max_x * (7/8); // how far the paddles are from each other

  int server = 0; // The player who is currently serving
  int points1 = 0; // Player 1's points
  int points2 = 0; // Player 2's points

  while(1) {
    clear();

    /* Header
        Displays who is currently serving
        Displays points for each player
    */
    mvprintw(0, 0, "Player %d is serving", server);
    mvprintw(1, 0, "Player 1: %d", points1);
    mvprintw(2, 0, "Player 2: %d", points2);

    refresh();

    usleep(DELAY);
  }

  endwin();
}
