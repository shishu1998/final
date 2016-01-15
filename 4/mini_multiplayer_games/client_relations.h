#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "connect4.h"
#include "dots.h"
#include "tictac.h"
#include "client_relations.h"

void choose_game(char * s){
  if (s.strcmp("1") == 0) {
    printf("You have chosen to play Connect 4\n");
    play_connect4();
  }
  else if (s.strcmp("2") == 0) {
    printf("You have chosen to play 
  }
