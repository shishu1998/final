#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

int main(){
    
  int p;
  p = fork();
  if (p != 0) {
    int status = 1;
    wait(&status);
    //return hold;
  }
  else {
    execlp("aplay", "aplay", "song.wav", 0);
  }
  return 0;

}