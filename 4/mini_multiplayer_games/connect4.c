#include <stdio.h>
#include <stdlib.h>

/*
  checkWin checks whether any of all of the possible
  winning scenarios are met. If it is, it sets wr1,
  wr2, wr3, wr4, cr1, cr2, cr3, & cr4 to the correct
  winning circles as well as the instance variable 
  "winner" to be true.
*/
private void checkWin(){
  int matches = 0;
  int r = 0;
  int c = 0;
  for (r = 0; r < 6; r++){
    for (c = 0; c < 4; c++){
      if (locations[r][c] != 'n'){
	if (locations[r][c] == locations[r][c+1]) matches++;
	if (locations[r][c] == locations[r][c+2]) matches++;
	if (locations[r][c] == locations[r][c+3]) matches++;
	if (matches == 3){
	  wr1 = wr2 = wr3 = wr4 = r;
	  wc1 = c;
	  wc2 = c + 1;
	  wc3 = c + 2;
	  wc4 = c + 3;
	  winner = true;
	}
      }
      matches = 0;
    }
  }
  for (c = 0; c < 7; c++){
    for (r = 0; r < 3; r++){
      if (locations[r][c] != 'n'){
	if (locations[r][c] == locations[r+1][c]) matches++;
	if (locations[r][c] == locations[r+2][c]) matches++;
	if (locations[r][c] == locations[r+3][c]) matches++;
	if (matches == 3){
	  wc1 = wc2 = wc3 = wc4 = c;
	  wr1 = r;
	  wr2 = r + 1;
	  wr3 = r + 2;
	  wr4 = r + 3;
	  winner = true;
	}
      }
      matches = 0;
    }
  }

  for (r = 0; r < 3; r++){
    for (c = 0; c < 4;c++){
      if (locations[r][c] != 'n'){
	if (locations[r][c] == locations[r+1][c+1]) matches++;
	if (locations[r][c] == locations[r+2][c+2]) matches++;
	if (locations[r][c] == locations[r+3][c+3]) matches++;
	if (matches == 3){
	  wr1 = r;
	  wr2 = r + 1;
	  wr3 = r + 2;
	  wr4 = r + 3;
	  wc1 = c;
	  wc2 = c + 1;
	  wc3 = c + 2;
	  wc4 = c + 3;
	  winner = true;
	}
      }
      matches = 0;
    }
  }

  for (r = 3; r < 6; r++){
    for (c = 0; c < 4; c++){
      if (locations[r][c] != 'n'){
	if (locations[r][c] == locations[r-1][c+1]) matches++;
	if (locations[r][c] == locations[r-2][c+2]) matches++;
	if (locations[r][c] == locations[r-3][c+3]) matches++;
	if (matches == 3){
	  wr1 = r;
	  wr2 = r - 1;
	  wr3 = r - 2;
	  wr4 = r - 3;
	  wc1 = c;
	  wc2 = c + 1;
	  wc3 = c + 2;
	  wc4 = c + 3;
	  winner = true;
	}
      }
      matches = 0;
    }
  }
}
