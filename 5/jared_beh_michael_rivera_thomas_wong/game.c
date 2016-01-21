#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "game.h"


void start_game() {
  // initialize empty board
  int R, C, r, c;

  for ( R = 0; R < 3; R++) {
    for ( C = 0; C < 3; C++) {

      for ( r = 0; r < 3; r++) {
	for ( c = 0; c < 3; c++) {
	  super_board[R][C].mini_board[r][c] = 0;
	}
      }

      super_board[R][C].winner = 0;

    }
  }

}

int turn(  char R, char C, char r, char c) {
  //react to player input

  return 0;
}

char check_super_win() {
  //check to see if the super_board is won
  int r, c;

  if ( ( super_board[0][2].winner == super_board[1][1].winner &&
	 super_board[1][1].winner == super_board[2][0].winner ) ||
       ( super_board[0][0].winner == super_board[1][1].winner &&
	 super_board[1][1].winner == super_board[2][2].winner ) ) {
    //if diagonals are all the same, return the winner
    //note that if a diagonal is all 0s, row/column wins are impossible
    return super_board[1][1].winner;
  }

  for ( c = 0; c < 3; c++) {
    if ( super_board[0][c].winner == super_board[1][c].winner &&
	 super_board[1][c].winner == super_board[2][c].winner ) {
      //if any column is all the same, return the winner
      return super_board[0][c].winner;
    }
  }

  for ( r = 0; r < 3; r++) {
    if ( super_board[r][0].winner == super_board[r][1].winner &&
         super_board[r][1].winner == super_board[r][2].winner ) {
      // if any row is all the same, return the winner
      return super_board[r][0].winner;
    }
  }

  return 0;

}

char check_win( char[][] mb ) {
  // check to see if a mini_board is won
  int r, c;

  if ( ( mb[0][2] == mb[1][1] &&
	 mb[1][1] == mb[2][0] ) ||
       ( mb[0][0] == mb[1][1] &&
	 mb[1][1] == mb[2][2] ) ) {
    //if diagonals are all the same, return the winner
    //note that if a diagonal is all 0s, row/column wins are impossible
    return mb[1][1];
  }

  for ( c = 0; c < 3; c++) {
    if ( mb[0][c] == mb[1][c] &&
	 mb[1][c] == mb[2][c] ) {
      //if any column is all the same, return the winner
      return mb[0][c];
    }
  }

  for ( r = 0; r < 3; r++) {
    if ( mb[r][0] == mb[r][1] &&
	 mb[r][1] == mb[r][2] ) {
      // if any row is all the same, return the winner
      return mb[r][0];
    }
  }

}
