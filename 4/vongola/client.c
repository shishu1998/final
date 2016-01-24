#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void process(int fd, int socket_id){
  char buffer[256];
  int num_bytes;

  if (fd == 0){
    //send from stdin to server
    fgets(buffer, sizeof(buffer), stdin);
    send(socket_id, buffer, strlen(buffer), 0);
  }else{
    //receive from server
    num_bytes=recv(fd, buffer, sizeof(buffer),0);
    if(num_bytes == -1){
      printf("recv: %s\n", strerror(errno));
      exit(0);
    }else if(num_bytes == 0){
      printf("Server closed\n");
      exit(0);
    }else{
      buffer[num_bytes]='\0';
      printf("RECEIVED:%s", buffer);
    }
  }
}

void setup_socket(int *socket_id){
 //create the socket
  *socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if(*socket_id == -1){
    printf("socket: %s\n", strerror(errno));
    exit(0);
  }

  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(56347);
  //Set the IP address to connect to
  //127.0.0.1 is the "loopback" address of any machine
  inet_aton("127.0.0.1", &(sock.sin_addr));
  if(connect(*socket_id, (struct sockaddr *)&sock, sizeof(sock)) == -1){
    printf("connect: %s\n", strerror(errno));
    exit(0);
  }

}

int main(int argc, char **argv) {

  int socket_id;
  char buffer[256];
  int i;
  fd_set master;
  fd_set read_fds;
  
  setup_socket(&socket_id);

  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  FD_SET(0, &master);
  FD_SET(socket_id, &master);

  int fdmax = socket_id;

  while (1){
    read_fds = master;
    if (select(fdmax+1, &read_fds, NULL, NULL, NULL)==-1){
      printf("select: %s\n", strerror(errno));
    }
    if(FD_ISSET(0, &read_fds)){
      process(0, socket_id);
    }
    if(FD_ISSET(socket_id, &read_fds)){
      process(socket_id, socket_id);
    }
  }

  return 0;
}
