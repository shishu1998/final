#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int playsong(){
  char * pointers[3];

  #ifdef LINUX
  pointers[0] = "mpg321";
  #else
  pointers[0] = "afplay";
  #endif
  pointers[1] = "State_of_Grace.mp3";
  pointers[2] = NULL;
  execvp(pointers[0], pointers);
  return 0;
}

int main(){
  playsong();
  return 0;
}
