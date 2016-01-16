#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "values.h"
#include "server.h"

//Need to be global for sighandler to work
int socket_id;
int socket_client;

static void sighandler(int signo){
  if (signo==SIGINT){
    close(socket_id);
    close(socket_client);
    exit(42);
  }
}

/*
if (stat("/root", &st) == -1) {
    mkdir("/root", 0700);
  }   

char *directory = "root";

  struct stat dir = {0};
  if(stat(directory, &dir) == -1) {
      mkdir(directory, 0755);
      printf("created directory testdir successfully! \n");
    }

  int filedescriptor = open(directory/"log.txt", O_RDWR | O_APPEND | O_CREAT);
  if (filedescriptor < 0) {
      perror("Error creating my_log file\n");
      exit(-1);
    }
*/

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
      if (ans='1'){
	//Check if user logged in
	//authenticate password. If correct, move on. Otherwise terminate
	//Put loop here
	//check for waiting mail
	//send size of mail to be sent in bytes (int). If none, 0
	//send mail
	//wait to recieve messages
	//pass on messages
	//check for mail, repeat above
      }
      //do child stuff
      close(socket_client);
      printf("Connection closed\n");
    }
  }
}
