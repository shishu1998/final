#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
//#include "connect4.h"
//#include "dots.h"
//#include "tictac.h"
#include "client_relations.h"



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
  
  socket_client = server_handshake(socket_id);
  client_connection(socket_client);
  
  return 0;
}

int server_handshake(int socket_id) {
  while (1) {
    listen(socket_id, 1);
    printf("<server> listening\n");
    int socket_client = accept(socket_id, NULL, NULL);
    int parent = fork();
    if (!parent) {
      printf("<server> connected: %d\n", socket_client);
      return socket_client;
    }
  }
}

void client_connection(int socket_client) {

  char * understanding;
  char buffer[256];
  while (read(socket_client, buffer, sizeof(buffer))) {
    printf( "<server> received [%s] from client %d\n", buffer, socket_client);
    understanding = understand(buffer);
    printf("i did done.\n");
    strcpy(buffer, understanding);
    printf("UNDERSTANDING %s\n",understand(buffer));
    write (socket_client, "bye", sizeof("bye"));
    strncpy(buffer, "", sizeof(buffer));
    printf("buffer:%s\n",buffer);
  }
  
}
