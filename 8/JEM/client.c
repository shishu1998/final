#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"

int send_note(int socket_client) {
  char* input = (char *)calloc( 256, sizeof(char) );
  printf( "Send to <other_client> : " );
  fgets(input, sizeof(input), stdin);
  input = strsep( &input, "\n" );
  write( socket_client, input, sizeof(input));
  printf( "[%s] has been written to the <server>!\n", input);
  return 0;
}

int recieve_note(int socket_id) {
  char buffer[256];
  read( socket_id, buffer, sizeof(buffer));
  printf("<client> received: [%s]\n", buffer );
  return 0;
}


int main(int argc, char **argv) {

  int socket_id;
  char buffer[256];
  int i;
  int end_chat = 1;

  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;   
  sock.sin_port = htons( my_port );
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  
  //attempt a connection
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);
  //Send & receive from server here!!!
  while(1) {
    sleep(1);
    read( socket_id, buffer, sizeof(buffer));
    printf("<client> received: [%s]\n", buffer );
  }
  return 0;
}
