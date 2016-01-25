#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

char *clientformat(char* input){
  if(input[0] == 'S'){
    //Text output starting with Server: ...
    printf("%s",input);
  }else if(input[0] == 'm'){
    //Move should update board
    updateboard(input[1],input[2],input[3]);
  }else if(input[0] == 'w'){
    //Win condition update
    winplayer = 
  }
  return boardstate;
}


char *serverformat(char *input){
}
