#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void process(int fd, int sockfd){
}

int main(int argc, char **argv) {

  int socket_id, fdmax;
  char buffer[256];
  int i;
  fd_set master;
  fd_set read_fds;


  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;   
  sock.sin_port = htons(24601);
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton( "127.0.0.1", &(sock.sin_addr) );
  //bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  if (connect(socket_id, (struct sockaddr *)&sock, sizeof(sock))==-1){
    printf("connect: %s\n", strerror(errno));
  }

  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  FD_SET(0, &master);
  FD_SET(socket_id, &master);

  fdmax=socket_id;
  while (1){
    read_fds = master;
    if (select(fdmax+1, &read_fds, NULL, NULL, NULL)==-1){
      printf("select: %s\n", strerror(errno));
    }
    for (i=0;i<=fdmax;i++){
      if (FD_ISSET(i, &read_fds)){
	process(i,socket_id);
      }
    }
  }
  //attempt a connection
  /*
  i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("<client> connect returned: %d\n", i);

  read( socket_id, buffer, sizeof(buffer));
  printf("<client> received: [%s]\n", buffer );
  */
  return 0;
}
