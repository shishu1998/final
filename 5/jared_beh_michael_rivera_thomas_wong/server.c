#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define READ 0
#define WRITE 1

int main() {
  int fds[2];
  int f = 1;
  int socket_id, socket_client;
  int port = 24600;
  int player_waiting = 0;
  char line[100];

  while(1){
    if(f){
      port++;

      //create the socket
      socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
      //bind socket to port/address
      struct sockaddr_in listener;
      listener.sin_family = AF_INET;  //socket type IPv4
      listener.sin_port = htons(port); //port #
      listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
      bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
      listen( socket_id, 1 );
      printf("<server> listening\n");

      socket_client = accept( socket_id, NULL, NULL );
      printf("<server> connected: %d\n", socket_client );

      if( player_waiting ){
	//SEND ADDRESS TO WAITING CHILD PROCESS THROUGH PIPE

      }
      else{
	//create a pipe to communicate with child
	pipe( fds );

	//fork off a new process
	f = fork();
      }
    }
    //errno is good
    if(f<0){
      printf("%s\n",strerror(errno) );
    }
    //instructions for the child
    if(!f){
      close(fds[WRITE]);
      read( fds[READ], line, sizeof(line) );
      close( fds[READ] );
      //client 2's address is now stored in line, we should SHAKE HANDS

    }
    //instructions for the parent
    else{
      //close connection to first client
      close(socket_id);
    }

    //write( socket_client, "hello", 6 );
  }
  return 0;
}
