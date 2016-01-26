#include <stdio.h>
#include <stdlib.h>

int checkWin(){
  int f = open("game.txt", O_RDONLY, 0666);
  char locations[6][7];
  read(f, &locations, sizeof(locations));
  int matches = 0;
  int r = 0;
  int c = 0;
  for (r = 0; r < 6; r++){
    for (c = 0; c < 4; c++){
      if (locations[r][c] != 'n'){
	if (locations[r][c] == locations[r][c+1]) matches++;
	if (locations[r][c] == locations[r][c+2]) matches++;
	if (locations[r][c] == locations[r][c+3]) matches++;
	if (matches == 3) return true;
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
	if (matches == 3) return true;
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
	if (matches == 3) return true;
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
	if (matches == 3) return true;
      }
      matches = 0;
    }
  }
  close(f);
  return false;
}
