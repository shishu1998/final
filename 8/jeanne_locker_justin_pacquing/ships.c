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

char uboard [6][6]; //your board
char oboard [6][6]; //your opponent's board
int shippies[5]; //the placement of your ships



/*======== void makeBoards() ==========
Inputs: none

Result: creates the displayed boards for play

====================*/
void makeBoards(){
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


/*======== int checkMatey() ==========
Inputs:
int guess: opponent's guess of where user's ship is
int places[]: user's ship placement

Result:
returns either 1 or 0: 1 if the guess hit, 0 if it didn't

====================*/
int checkMatey(int guess, int places[]){
  int ind = 0;
  int result = 0;
  while (places[ind] != NULL){
    if (places[ind] == guess){
      result = 1;
    } else {
      ind++;
    }
  }
  return result;
}


int play(){

  int pos;
  
  printf("Ahoy, matey! Welcome to Battleship Bash Bros.\n");
  //insert grid setup
  printf("It's time to arrange your fleet.\n");
  //printf("Input where you want the leftmost or topmost part of your ship: ");
  makefleet(shippies);
  
  
  
  //a bunch of stuff
  return 0;
}
