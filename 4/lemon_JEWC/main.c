#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>

int main(){
  printf("\e[7mPlease enter the name of the file you are creating or editing.\e[27m\n");
  char response[100];
  fgets(response,100,stdin);
  printf("Your response was %s",response);



  return 0;
}
