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
  char sen[256];
  char rec[256];
  int num_bytes;

  if (fd==0){//send
    fgets(sen, sizeof(sen), stdin);
    send(sockfd, sen, sizeof(sen), 0);
  }else{//receive
    num_bytes=recv(sockfd,rec,sizeof(rec),0);
    rec[num_bytes]='\0';
    printf("SENT:%s\n", rec);
    fflush(stdout);
  }
}

int main(int argc, char **argv) {

  int socket_id, fdmax;
  char buffer[256];
  int i;
  fd_set master;
  fd_set read_fds;


  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_id == -1){
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
  if(connect(socket_id, (struct sockaddr *)&sock, sizeof(sock)) == -1){
    printf("connect: %s\n", strerror(errno));
    exit(0);
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

  return 0;
}
