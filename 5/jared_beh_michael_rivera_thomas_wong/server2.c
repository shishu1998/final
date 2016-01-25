#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "game.h"
#include "shared.h"

int socket_id, socket_client;
int socket_id_2, socket_client_2;
char line[100];
char prev[2];

static void sighandler( int signo ) {

  if ( signo == SIGINT ) {
    printf("Interrupted... how rude!\n");
    line[0]='F';
    line[1]='A';
    line[2]='I';
    line[3]='L';
    write(socket_id,line,4);
    close(socket_id);
    write(socket_id_2,line,4);
    close(socket_id_2);
    exit(0);
  }
}
int main() {
  /*

*/
  struct sockaddr_in listener;

  int f=1;

  while(1){
    if(f){
      //create the socket
      socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
      //bind to port/address
      listener.sin_family = AF_INET;  //socket type IPv4
      listener.sin_port = htons(24601); //port #
      listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
      bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
      listen( socket_id, 1 );
      printf("<server> listening\n");

      socket_client = accept( socket_id, NULL, NULL );
      printf("<server> connected: %d\n", socket_client );

      //write( socket_client, "hello", 6 );
  
      ///////////////////////////////////////////////////
  
      //create the socket
      socket_id_2 = socket( AF_INET, SOCK_STREAM, 0 );
  
      //bind to port/address
      struct sockaddr_in listener;
      listener.sin_family = AF_INET;  //socket type IPv4
      listener.sin_port = htons(24601); //port #
      listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
      bind(socket_id_2, (struct sockaddr *)&listener, sizeof(listener));
  
      listen( socket_id_2, 1 );
      printf("<server> listening\n");

      socket_client_2 = accept( socket_id_2, NULL, NULL );
      printf("<server> connected: %d\n", socket_client_2 );

      //write( socket_client_2, "hello", 6 );
      f = fork();
    }
    //errno
    if(f<0){
      printf("%s\n",strerror(errno) );
    
    }
    //instructions for child
    if(!f){
      write( socket_client, line, 4 );
      read( socket_id, line, 4 );
      turn( line[0],line[1],line[2], line[3] );
      write( socket_client_2, line, 4 );
      read(socket_id_2, line, 4);
      turn( line[0],line[1],line[2], line[3] );
    }
    else{
      //close connections
      close(socket_id);
      close(socket_id_2);
    }
  }
  return 0;
  
}
