#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "login.h"

int main() {
  char* yes_or_no = (char*)malloc(sizeof(char)*10);
  char* input = (char*)malloc(sizeof(char)*250);
  char* buffer = (char*)malloc(sizeof(char)*250);
  int socket_id, socket_client, con_id;
  
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(24601); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 1 );
  
  for ( ; ; ) {

    socket_client = accept(socket_id, NULL, NULL); // blocking call 
    //int pid = fork();

    //if ( pid == 0 ) { //check for child

    close(socket_id);
    printf("<server> connected: %d\n", socket_client );
    //now you can do things
    //while( strcmp(input, "bye") != 0 ) {
    while( 1 ) {
      printf("Talk to <client> : ");
      //fgets(input, strlen(input), stdin);
      fgets(input, msg_len, stdin);
      //input = strsep(&input, "\n");
      strtok(input, "\n");
      //write( socket_client, input, strlen(input));
      write( socket_client, input, msg_len );
      if ( strcmp( input, exit_sig ) == 0 ) {
	printf(">> Are you sure you want to exit?\n");
	printf(">> type 'y' for yes\n>> type 'n' for no\n");
	fgets( yes_or_no, 10, stdin);
	strtok(yes_or_no, "\n");

	if ( strlen(yes_or_no) > 1 ) {
	  printf( ">> Looks like you goofed!  Better just keep chatting...\n");
	  printf( "Wait for your partner to respond...\n");
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
      //read( socket_client, buffer, strlen(buffer));
      read( socket_client, buffer, msg_len);
      printf("<server> received: [%s]\n", buffer );
    }
    close(socket_client);
    exit(0); 
    //}
  }
}
 

