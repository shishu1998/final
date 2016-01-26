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
int shippies[5] = {0,0,0,0,0}; //the placement of your ships

/*======== void makeBoards() ==========
Inputs: none

Result: creates the displayed boards for play

====================*/
void makeBoards(){
  //edges
  int d = 1;
  int a = 0;
  //char c;
  while (d < 6){
    //char c = (char)d;
    //printf("%c ", c);
    // printf("%d ", d);
    uboard[d][a] = d;
    oboard[d][a] = d;
    d++;
  }
  d = 0;
  a = 1;
  while (a < 6){
    //char b = (char)a;
    //printf("%c ", b);
    uboard[d][a] = a;
    oboard[d][a] = a;
    a++;
  }
  //fill board
  d = 1;
  a = 1;
  while (d<6){
    while(a<6){
      uboard[d][a] = '.';
      oboard[d][a]='.';
      a++;
    }
    d++;
    a=1;
  }
  //printf("%c ", uboard[1][1]);
  //printf("%c ", uboard[1][3]);
  //printf("%c ", uboard[2][3]);
  //printf("%d ", uboard[0][3]);
}


/*======== void printBoards() ==========
Inputs:
none

Result:
prints them boards

====================*/
void printBoards(){
  int d=0;
  int a=0;
  printf("Your Board");
  while (d<6){
    while (a<6){
      if (d==0 || a==0){
      printf("%d", uboard[d][a]);
      a++;
      } else {
	printf("%c", uboard[d][a]);
	a++;
      }
    }
    printf("\n");
    d++;
  }
  printf("\n");

  d=0;
  a=0;
  printf("Your Opponent's Board");
  while (d<6){
    while (a<6){
     if (d==0 || a==0){
      printf("%d", uboard[d][a]);
      a++;
      } else {
	printf("%c", uboard[d][a]);
	a++;
      }
    }
    printf("\n");
    d++;
  }
}

int main(){
  makeBoards();
  printBoards();
  return 0;
}
