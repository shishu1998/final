#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"

int pass_note( int client_from, int client_to, char* note ) {
  read(client_from, note, sizeof(note));
  printf("<server> received [%s]\n", note);
  write(client_to, note, sizeof(note));
  printf("<server> sent [%s]\n", note);
  return 0;
}

int main() {

  char input[256];
  char buffer[256];
  int socket_id, socket_client, con_id;
  
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons( my_port ); //port #
  //listener.sin_port = htons(24600); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 100 );
  printf("<server> listening\n");

  for ( ; ; ) {
    
    socket_client = accept(socket_id, NULL, NULL); // blocking call 
    int pid = fork(); //open the subserver for this client

    if ( pid == 0 ) { //check for child this is the subserver now!!
      printf("<server> connected: %d\n", socket_client );
      while(1){
	sleep(1);
	write( socket_client, "success", 8 );
      }
      close(socket_client);
      exit(0); 
    }
  }
}
