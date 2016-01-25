#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {

  int socket_id, socket_client;
  char buffer[256];
  int hit;
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(24601); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  while(1){
  
  listen( socket_id, 1 );
  printf("<server> listening\n");

  socket_client = accept( socket_id, NULL, NULL );
  printf("<server> connected: %d\n", socket_client );
 
  // printf("\n");

  if( socket_client % 2 ) // figure out which player is contacting the server
    write( socket_client, "Player 2", 100 );
  else
    write( socket_client, "Player 1", 100 );

  read( socket_client, buffer, sizeof(buffer) ); // read what the player has sent
  printf( "<server> Client returned: %s\n", buffer );

  // check if what the player has sent is a hit/miss
  //im assuming we can use the board.c functions for this (change truth value of hit)


  // tell them that they have hit/missed
  if ( hit )
    write( socket_client, "You have hit a ship!", 100 );
    //change board
  else 
    write( socket_client, "You have missed!", 100 );
  }

  return 0;
}
