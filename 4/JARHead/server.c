
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void process( char *s ) {
  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}

int main() {

  int socket_id, socket_client;
  int pid, status;
  char buffer[256];

  // create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET; // socket type IPv4
  listener.sin_port = htons(5000); // port #
  listener.sin_addr.s_addr = INADDR_ANY; // bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));

  listen( socket_id, 1 );
  printf("<server> listening\n");

  while (1) {
    socket_client = accept( socket_id, NULL, NULL );
    printf("<server> connected: %d\n", socket_client );

    if ( (pid = fork()) == 0 ) {
      while(1) {
        recv(socket_client, buffer, sizeof(buffer), 0 );
        printf("%s", buffer);
        strtok(buffer, "\n");
        // process(buffer);
        send(socket_client, buffer, sizeof(buffer), 0 );
      }
    }
    else {
      close(socket_client);
    }
  }
  return 0;
}
