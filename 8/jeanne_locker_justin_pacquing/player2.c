#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>

int ships[5] = {0, 0, 0, 0, 0};

int client_handshake(int *from_server){
  int to_server;
  char buffer[100];

  //server does it's end of the handshake and waits for client
  //client makes a "private" (pid) named pipe
  sprintf(buffer, "%d", getpid());
  mkfifo(buffer, 0644);
  //client connects to server and sends pipe name
  to_server = open("popeye", O_WRONLY);
  //printf("went into popeye\n");
  write(to_server, buffer, sizeof(buffer));
  //client recieves client's message and removes wkp
  //server connects to client's pipe and send message
  *from_server = open(buffer, O_RDONLY);
  remove(buffer);
  //client recieves server's message, removes private pipe
  read(*from_server, buffer, sizeof(buffer));

  printf("Captian %d, Enemy Message Incoming: %s\n", getpid(),buffer);

  return to_server;
}

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("\nYou're done with %d\n", getpid());
    exit(0);
  }
}

int main(){
  signal(SIGINT, sighandler);

  int to_server;
  int from_server;
  char buffer[100];

  makeFleet();
  
  to_server = client_handshake(&from_server);

  while(1){
    printf("Client %d says: ", getpid());
    fgets(buffer, sizeof(buffer), stdin);
    strtok(buffer, "\n");
    if(strcmp(buffer, "exit")==0){
      printf("\nYou're done with %d\n", getpid());
      break;
    }
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer, sizeof(buffer));
    printf("Server says: %s", buffer);
  }

  close(to_server);
  close(from_server);

  return 0;
}
