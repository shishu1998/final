#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"

int main() {

  char input[256];
  char buffer[256];
  int socket_id, socket_client, con_id;
  
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(24601); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 100 );
  
  for ( ; ; ) {

    socket_client = accept(socket_id, NULL, NULL); // blocking call 
    int pid = fork();

    if ( pid == 0 ) { //check for child

      close(socket_id);
      printf("<server> connected: %d\n", socket_client );
      //now you can do things
      while( strcmp(input, exit_sig) != 0 ) {
	printf("Talk to <client> : ");
	fgets(input, sizeof(input), stdin);
	write( socket_client, input, sizeof(input));

	read( socket_client, buffer, sizeof(buffer));
	printf("<server> received: [%s]\n", buffer );
      }
      close(socket_client);
      exit(0); 
    }
  }
}
 

