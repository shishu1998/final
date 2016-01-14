#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

static void sighandler( int signo ){

  int i,n;
  time_t t;

  srand((unsigned) time(&t));
  n = rand() % 3;
    
  if (signo == SIGINT){
    printf("You waved the white flag\n");
    if (n == 1){
      printf("What a sore loser!\n");
    }
    else printf ("It's ok! Try again next time!\n");
    exit(0);
  }
}

int main(){
  
  signal(SIGINT,sighandler);
  
  while(1){
    printf("this keeps going \n");
    sleep(1);
  }
  return 0;
}
