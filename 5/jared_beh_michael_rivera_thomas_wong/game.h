#ifndef GAME_H
#define GAME_H

void board_init();            // initialize empty board
int turn( char player, int R, int C, int r, int c);    // react to legal or illegal player input
char check_win();  // check to see if the super_board is won
void update_winner( board );  // update winner variable
void update_full( board );    // update full variable

#endif
