#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>

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
  listener.sin_port = htons(5000); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 1 );

  while(1){

    printf("<server> listening\n");
    socket_client = accept( socket_id, NULL, NULL );
    printf("<server> connected: %d\n", socket_client );

    if (fork() == 0){
      
      printf("Enter text to write:\n");
      char s[100];
      fgets(s, sizeof(s), stdin);
      write(socket_client, s, sizeof(s));
      printf("<server> waiting\n");
      sleep(2);
      read(socket_client, s, sizeof(s));
      printf("<server> received: %s\n", s);

    }else{
      close(socket_client);
    }
  }

  return 0;
}
