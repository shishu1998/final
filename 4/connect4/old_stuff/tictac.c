#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
  parent = fork();
  if (!parent) {
    execlp("cat","cat","tictac_help.txt",NULL);
  }
}

void play_move() {
  
}
