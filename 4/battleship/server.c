#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main() {

  int socket_id, socket_client;
  
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
    if( socket_client % 2 ){
      write( socket_client, "P2:", 6 );
    }
    else{
      write( socket_client, "P1:", 6 );
    }
  }
  return 0;
}
//something is broken
