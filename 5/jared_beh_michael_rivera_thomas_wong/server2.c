#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "game.h"

  int socket_id, socket_client;
  int socket_id_2, socket_client_2;
  char line[100];

static void sighandler( int signo ) {
  int *addr_socket_id, *addr_socket_client;
  int *addr_socket_id_2, *addr_socket_client_2;
  char *addr_line[100];
  if ( signo == SIGINT ) {
    printf("Interrupted... how rude!\n");
    *addr_line[0]='3';
    write(socket_id,*addr_line,sizeof(*addr_line));
    close(*addr_socket_id);
    write(*addr_socket_id_2,*addr_line,sizeof(*addr_line));
    close(*addr_socket_id_2);
    exit(0);
  }
}
int main() {

  int *addr_socket_id, *addr_socket_client;
  int *addr_socket_id_2, *addr_socket_client_2;
  int f=1;
  char *addr_line[100];

  while(1){
    if(f){
      //create the socket
      *addr_socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
      //bind to port/address
      struct sockaddr_in listener;
      listener.sin_family = AF_INET;  //socket type IPv4
      listener.sin_port = htons(24601); //port #
      listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
      bind(*addr_socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
      listen( *addr_socket_id, 1 );
      printf("<server> listening\n");

      *addr_socket_client = accept( *addr_socket_id, NULL, NULL );
      printf("<server> connected: %d\n", *addr_socket_client );

      //write( socket_client, "hello", 6 );
  
      ///////////////////////////////////////////////////
  
      //create the socket
      *addr_socket_id_2 = socket( AF_INET, SOCK_STREAM, 0 );
  
      //bind to port/address
      struct sockaddr_in listener;
      listener.sin_family = AF_INET;  //socket type IPv4
      listener.sin_port = htons(24601); //port #
      listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
      bind(*addr_socket_id_2, (struct sockaddr *)&listener, sizeof(listener));
  
      listen( *addr_socket_id_2, 1 );
      printf("<server> listening\n");

      *addr_socket_client_2 = accept( *addr_socket_id_2, NULL, NULL );
      printf("<server> connected: %d\n", *addr_socket_client_2 );

      //write( socket_client_2, "hello", 6 );
      f = fork();
    }
    //errno
    if(f<0){
      printf("%s\n",strerror(errno) );
    
    }
    //instructions for child
    if(!f){
      write( *addr_socket_client, *addr_line, sizeof(*addr_line) );
      read( *addr_socket_client, addr_line, 4 );
      turn( *addr_line[0],*addr_line[1],*addr_line[2], *addr_line[3] );
      write( *addr_socket_client_2, *addr_line, sizeof(*addr_line) );
      read(*addr_socket_2, addr_line, 4);
      turn( *addr_line[0],*addr_line[1],*addr_line[2], *addr_line[3] );
    }
    else{
      //close connections
      close(*addr_socket_id);
      close(*addr_socket_id_2);
    }
  }
  return 0;
  
}
