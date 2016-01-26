#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

int chandshake(int *from_server){
  int to_server;
  char buffer[1024];
  
  sprintf(buffer, "%d", getpid());
  mkfifo(buffer, 0644);
  
  to_server = open("HANGMAN", O_WRONLY);
  write(to_server, buffer, sizeof(buffer));

  *from_server = open(buffer, O_RDONLY);
  remove(buffer);
  read(*from_server, buffer,sizeof(buffer));

  printf("Handshake.\n");

  return to_server;
}

static void sighandler(int signo){
  if(signo ==SIGINT){
    remove("HANGMAN");
    exit(0);
  }
}

int main(){
  signal(SIGINT, sighandler);

  int to_server;
  int from_server;
  char buffer[1024];

  to_server = chandshake(&from_server);
  

  while(read(from_server,buffer,sizeof(buffer))){
    printf("%s\n", buffer);
    int LINE_CAP = 1024;
    char line[LINE_CAP];
    printf("\nEnter guess (single char or full word):");
    fgets(line, LINE_CAP,stdin);
    if(line[strlen(line)-1]=='\n')
      line[strlen(line)-1] = '\0';
    write(to_server, line, sizeof(line));
  }
  return 0;
}
