#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>

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

  listen( socket_id, 1 );
  printf("<server> listening\n");

  int pid = 0;
  
  while ( 1 ) {
    socket_client = accept( socket_id, NULL, NULL );
    if (socket_client < 0)
      printf("ERROR on accept\n");
    pid = fork();
    if (pid < 0)
      printf("ERROR on fork\n");
    if (pid == 0)  {
      close(socket_id);
      printf("[child] eric sucks\n");
      exit(0);
    }
    else close(socket_client);
  }

    printf("<server> connected: %d\n", socket_client );

    write( socket_client, "hello", 6 );

    close(socket_client);
    close(socket_id);




  return 0;
}
