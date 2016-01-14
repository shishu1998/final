#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
 
#define PORTNUM 2300
 
int is_exit(char buf[],int to_client,int from_client){
  if (strcmp(buf,"exit")==0){
    close(to_client);
    close(from_client);
    printf("Client has disconnected\n");
    return 1;
  }
  return 0;
}

static void sighandler(int signo){
  if (signo==SIGINT){
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
      //do child stuff
      write(socket_client,"hello",6);
      close(socket_client);
      printf("Connection closed\n");
    }
  }
}
