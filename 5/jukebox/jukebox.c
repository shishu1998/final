
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int new_client(socket_client){
  //socket client is now fd 
  //interact with client
  char * lyric = "Pardon me, are you Aaron Burr, sir?";
  while(1)
  write(socket_client, lyric, sizeof(lyric));
  exit(0);
}


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
  printf("The jukebox server is up and running and waiting for clients to connect.\n");

  while (1) {
    socket_client = accept( socket_id, NULL, NULL );
    printf("<server> connected: %d\n", socket_client );
    int cpid = fork();
    if (cpid == 0){
      new_client(socket_client);
    }
  }
  return 0;
}
