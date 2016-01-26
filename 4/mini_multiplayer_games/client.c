#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//This is just copied from your source code (mostly)
int client_handshake( int *from_server ) {

  int to_server;
  char buffer[100];

  sprintf(buffer, "%d", getpid() );
  mkfifo( buffer, 0644 );

  printf("Awaiting connection \n");
  to_server = open( "aaron", O_WRONLY );
  write( to_server, buffer, sizeof(buffer) );

  *from_server = open( buffer, O_RDONLY );
  remove( buffer );

  read( *from_server, buffer, sizeof(buffer) );
  printf("Connection Established: [%s]\n", buffer );

  return to_server;
}


int main() {

  int to_server;
  int from_server;
  char buffer[100];
  printf("If you wish to exit, you must connect first\n");
  to_server = client_handshake( &from_server );

  while (1) {
    printf("Type in an amazing line: \n");
    fgets( buffer, sizeof(buffer), stdin );
    *strchr( buffer, '\n') = 0;
    if (strcmp(buffer,"exit") == 0) exit(0);
    write( to_server, buffer, sizeof(buffer) );
    read( from_server, buffer, sizeof(buffer) );
    printf("<client> received: [%s]\n", buffer );
  }

  close( to_server );
  close( from_server );

  return 0;
}
