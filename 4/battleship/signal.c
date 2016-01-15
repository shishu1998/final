#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

static void sighandler( int signo ){

  int i,n,end,win;
  time_t t;

  srand((unsigned) time(&t));
  n = rand() % 3;
  end = 0;

  if (signo == SIGINT){
    if (end == 0){
      printf("You waved the white flag\n");
    if (n == 1){
      printf("What a sore loser!\n");
      printf("You will never bring honor to your family!\n");
	}
    else printf ("It's ok! Try again next time!\n");
    }
    else 
      printf ("You faught well, See you on the battle field next time\n");
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
