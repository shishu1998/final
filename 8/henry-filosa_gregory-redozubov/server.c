#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "values.h"
#include "server.h"

static void sighandler(int signo){
  if (signo==SIGINT){
    exit(42);
  }
}

void get_user(char * ans, char name[], char password[], int socket_client){
  int error=read(socket_client,ans,1);
  if (error==-1){
    printf("Error recieving ANS: %s\n",strerror(errno));
    exit(42);
  }
  read(socket_client,name,NAME_LEN);
  if (error==-1){
    printf("Error recieving NAME: %s\n",strerror(errno));
    exit(42);
  }
  read(socket_client,password,PASS_LEN);
  if (error==-1){
    printf("Error recieving PASSWORD: %s\n",strerror(errno));
    exit(42);
  }
}
int main(int argc, char *argv[]){
  signal(SIGINT,sighandler);
  int socket_id, socket_client;
  int child_pid;
  socket_id = socket( AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in listener;
  listener.sin_family = AF_INET; //socket type to IPv4
  listener.sin_port = htons(PORTNUM); //port # 
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  listen(socket_id,1);
  printf("Socket established\n");
  while(1){
    printf("<Server> waiting for connection\n");
    socket_client = accept(socket_id, NULL, NULL);
    printf("Connection established\n");
    child_pid=fork();
    if (child_pid==0){
      printf("Child process\n");
      char ans;
      char name[NAME_LEN];
      char password[PASS_LEN];
      get_user(&ans,name,password,socket_client);
      printf("ANS: %c NAME: %s PASSWORD: %s\n",ans,name,password);
      //do child stuff
      close(socket_client);
      printf("Connection closed\n");
    }
  }
}
