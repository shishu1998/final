#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

int main(){
    
  /*int p;
  p = fork();
  if (p != 0) {
    int status = 1;
    wait(&status);
  }
  else {
  */
    execlp("aplay", "aplay", "song.mp3", 0);
  
  
  //printf("hello\n");
  return 0;

}