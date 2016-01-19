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

int setup(){

  printf("Ahoy, matey! Welcome to Battleship Bash Bros.");
  //insert grid setup
  printf("It's time to arrange your fleet.");
  printf("Input where you want the leftmost or topmost part of your ship:");
  printf("");
  //a bunch of stuff
  return 0;
}
