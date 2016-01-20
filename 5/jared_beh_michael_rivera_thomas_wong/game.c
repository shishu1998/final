#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "game.h"

void error_check( int e ) {
  // defensive programming!
  if ( e < 0 ) {
    printf( "ERROR #%d: %s\n", errno, strerror(errno) );
    end_game();
  }
}

void start_game() {
  // initialize empty board, random choose first player
  int R, C, r, c;

  for ( R = 0; R < 3; R++) {
    for ( C = 0; C < 3; C++) {
      for ( r = 0; r < 3; r++) {
	for ( c = 0; c < 3; c++) {
	  super_board[R][C].mini_board[r][c] = 0;
	  super_board[R][C].winner = 0;
	}
      }
    }
  }

}

void turn( board[][], char R, char C, char r, char c) {
//react to player input

}


char check_win( char[][] mini_board ) {
// check to see if a board is won
  char output;
  int r, c;

  for ( r = 0; r < 3; r++) {
    for ( c = 0; c < 3; c++) {

      if ( mini_board[r][c] ) {
	
      }

    }
  }

}

void end_game() {
// exit message, close connections, quit game.

}

char* parse( board[][] ) {
// prepare String for client.

}
