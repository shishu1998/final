#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>

void *handle_client(void *arg)

int main(int argc, char *argv[]){
  int servefd = 0;
  int connfd = 0;
  int n = 0;
  struct sockaddr_in serve;
  struct sockaddr_in clint;

  //set servefd
  servefd = socket(AF_INET, SOCK_STREAM, 0);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonly(INADDR_ANY);
  serv_addr.sin_port = htons(8000);

  //bind and check
  if(bind(servefd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    perror("Socket binding failed");
    return 1;
  }

  
  if(listen(servefd, 10) < 0){
    perror("Socket listening failed");
    return 1;
  }
  
  printf("***SERVER STARTED***\n");

  while (1) {
    int clilen = sizeof(cli_addr);
    connfd = accept(servefd, (struct sockaddr*) & cli_addr, &clilen);
    sleep(1); //reduce cpu usage
  }
  
}

