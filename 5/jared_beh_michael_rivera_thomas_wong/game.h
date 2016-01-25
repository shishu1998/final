#IFNDEF GAME_H
#DEFINE GAME_H

typedef struct {

  char mini_board[3][3];  // Each board is 3x3 board!
  char winner;            // 0, X, O who won this board?
  char full;              // 0, 1 is this board full?

} board;

extern board super_board[3][3];

void board_init();            // initialize empty board
int turn( int R, int C, int r, int c);    // react to legal or illegal player input
char check_win();  // check to see if the super_board is won
void update_winner( board );  // update winner variable
void update_full( board );    // update full variable

#ENDIF
