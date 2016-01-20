//http://stackoverflow.com/questions/7808331/how-to-connect-two-clients-from-the-server

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

  while(1){

    printf("<client> waiting\n");
    char s[100];
    sleep(1);
    read(socket_id, s, sizeof(s));
    printf("<client> received: %s\n", s);
    printf("Enter text to write:\n");
    fgets(s, sizeof(s), stdin);
    write(socket_id, s, sizeof(s));

  }

  // read( socket_id, buffer, sizeof(buffer));
  //printf("<client> received: [%s]\n", buffer );
  
  return 0;
}
