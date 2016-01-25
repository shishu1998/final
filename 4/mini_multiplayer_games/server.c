#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


static void sighandler( int signo ) {
  if (signo == SIGINT) {
    remove("aaron");
    exit(0);
  }
}


int server_handshake( int *from_client ) {

  int to_client;
  char buffer[100];
  int parent;
  printf("Looking for new connection\n");
  while (1) {
    mkfifo( "aaron", 0644 );
    *from_client = open( "aaron", O_RDONLY );

    remove( "aaron" );

    read( *from_client, buffer, sizeof(buffer) );

    parent = fork();
    if (!parent) {
      printf( "<server> connection established: [%s]\n", buffer );
      to_client = open( buffer, O_WRONLY ); //connect downstream

      strncpy( buffer, "You found aaron.", sizeof(buffer) );
      write( to_client, buffer, sizeof(buffer) ); //send initial message
      printf("Looking for new connection\n");
      return to_client;
    }
  }
}

void process( char *s ) {
  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}

void client_connection( int to_client, int from_client ) {

  char buffer[100];

  while( read( from_client, buffer, sizeof(buffer) ) ) {

    printf( "<server> received [%s] from client %d\n", buffer, getpid() - 1);
    process( buffer );
    write( to_client, buffer, sizeof(buffer) );

    strncpy( buffer, "", sizeof(buffer) );
  }
}

int main() {

  int to_client;
  int from_client;

  signal(SIGINT,sighandler);

  printf("<server> waiting for connection\n");
  to_client = server_handshake( &from_client );

  client_connection( to_client, from_client );

  close( to_client );


  return 0;
}
