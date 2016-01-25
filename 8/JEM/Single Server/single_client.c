#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "login.h"

int main(int argc, char **argv) {

  int socket_id;
  //char input[256];
  //char buffer[256];
  char* yes_or_no = (char*)malloc(sizeof(char)*10);

  char* input = (char*)malloc(sizeof(char)*250);
  char* buffer = (char*)malloc(sizeof(char)*250);
  int i;

  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;   
  sock.sin_port = htons(24601);
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  
  //attempt a connection
  //if (find_user_match() == 1) {
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
    printf("<client> connect returned: %d\n", i);
    if ( i < 0 ){
      printf("We're sorry, you failed to connect to the server.  Please try again.\n");
      exit(0);
    }
    //}
  //while (strcmp(buffer, "bye") != 0) {
  while( 1 ) {
    //read( socket_id, buffer, strlen(buffer));
    read( socket_id, buffer, msg_len);
    printf("<client> received: [%s]\n", buffer );
    printf("Talk to <server> : ");
    //fgets(input, strlen(input), stdin);
    fgets(input, msg_len, stdin);
    strtok(input, "\n");
    //write( socket_id, input, strlen(input));
    write( socket_id, input, msg_len);
    if ( strcmp( input, exit_sig ) == 0 ) {
      printf(">> Are you sure you want to exit?\n");
      printf(">> type 'y' for yes\n>> type 'n' for no\n");
      fgets( yes_or_no, 10, stdin);
      strtok(yes_or_no, "\n");

      if ( strlen(yes_or_no) > 1 ) {
	printf( ">> Looks like you goofed!  Better just keep chatting...\n");
      }
      else if ( strcmp( yes_or_no, "y" ) == 0) {
	printf(">> You're gone!\n");
	exit(0);
      }
      else {
	printf( ">> Then why did you say bye???\n" );
	printf( "Wait for your partner to respond...\n");
      }

    }
  }
  
  return 0;
}
