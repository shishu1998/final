#include <stdlib.h>
#include <stdio.h>

#include <string.h> 
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv){
  
  int socket_id, errno,i;
  char buffer[256];

  //creating the socket 
  socket_id = socket(AF_INET, SOCK_STREAM, 0);

  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  inet_aton("127.0.0.1", &(sock.sin_addr));
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  
  
  //attempt to make a connection
  i = connect(socket_id, (struct sockaddr*)&sock, sizeof(sock));
  if (i == -1) {
    printf("<client>Error connecting to server: %s\n", strerror(errno));
    return 0;
  }
  else{
    printf("<client> Connection made to %d\n", socket_id);
  }
  while (1){
    printf("Enter Message:");
    fgets(buffer, 256, stdin); //replace this buffer with some type of int to send to server
    send(socket_id, buffer, sizeof(buffer), 0);
    recv(socket_id, buffer, sizeof(buffer), 0);
    printf("<client> received [%s]\n\n", buffer);
  }

  return 0;
}
