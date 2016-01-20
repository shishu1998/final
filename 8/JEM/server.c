#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {

int socket_id, socket_client;

socket_id = socket( AF_INET, SOCK_STREAM, 0 );

struct sockaddr_in listener;

listener.sin_family = AF_INET;  //socket type IPv4
listener.sin_port = htons(24601); //port #
listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
listen( socket_id, 1 );
printf("<server> listening\n");

socket_client = accept( socket_id, NULL, NULL );
printf("<server> connected: %d\n", socket_client );

write( socket_client, "hello", 6 );
  
return 0;
}
