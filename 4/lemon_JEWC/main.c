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
  strtok(response,"\n");
  if(access(response,F_OK)!=-1){
    printf("\e[7m%s\e[27m exists. Now opening.\n\n",response);
    execlp("cat","cat",response,NULL);
  }
  else{
    printf("\e[7m%s\e[27m does not exist. Now creating.\n",response);
  }


  return 0;
}
