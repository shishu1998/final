// trad. board is 10x10
// aircraft carrier (5),battleship (4),
// submarine (3), destroyer (3), patrol boat(2)

//create blank board, prompt user to input ships, edit

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

char uboard [11][11]; //your board
char oboard [11][11]; //your opponent's board


/*======== void makeboards() ==========
Inputs:

Result:

====================*/
void makeboards(){
  int d = 1;
  int a = 0;
  while (d < 11){
    uboard [d][a] = d;
    obard [d][a] = d;
    d++;
  }
  d = 0;
  a = 1;
  while (a<11){
    uboard [d][a] = a;
    oboard [d][a] = a;
    a++;
  }
}

int setup(){

  int pos;
  
  printf("Ahoy, matey! Welcome to Battleship Bash Bros.");
  //insert grid setup
  printf("It's time to arrange your fleet.");
  //printf("Input where you want the leftmost or topmost part of your ship: ");
  printf("Input where you want your ship! Each ship is one unit: ");
  scanf("%s", &pos);
  
  //a bunch of stuff
  return 0;
}
