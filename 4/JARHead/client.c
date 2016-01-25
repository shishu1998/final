#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv) {

  int socket_id;
  char buffer[256];
  int i;
  int errno;

  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));

  //attempt a connection
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);

  while(1) {
    errno = recv( socket_id, buffer, sizeof(buffer), 0);
    printf("Error: %s\n", strerror(errno));
    printf("Received: %s\n", buffer);
    printf("Enter A Message\n");
    fgets(buffer, 256, stdin);
    send( socket_id, buffer, sizeof(buffer), 0);
  }

  return 0;
}
