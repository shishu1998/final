#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void process(int fd, fd_set *master, int socket_id, int fdmax){
  char buffer[256];
  int num_bytes;
  num_bytes = recv(fd, buffer, sizeof(buffer), 0);
  if(num_bytes <= 0){
    if(num_bytes == -1){
    printf("recv: %s\n", strerror(errno));
    }else if(num_bytes == 0){
      printf("Socket %d has closed", fd);
    }
    close(fd);
    FD_CLR(fd, master);
  }else{
    buffer[num_bytes]='\0';
    int i;
    for(i = 3;i <= fdmax; i++){
      if(i != fd && i != socket_id && FD_ISSET(i, master)){
	if(send(i, buffer, strlen(buffer), 0) == -1){
	  printf("send %s\n", strerror(errno));
	}
      }
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

  int on = 1;

  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(56347); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  if(setsockopt(*socket_id, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(*socket_id)) == -1){
    printf("setsockopt %s\n", strerror(errno));
    exit(0);
  }
  if(bind(*socket_id, (struct sockaddr *)&listener, sizeof(listener)) == -1){
    printf("bind: %s\n", strerror(errno));
    exit(0);
  }
  
  if(listen(*socket_id, 15) == -1){
    printf("listen: %s\n", strerror(errno));
    exit(0);
  }
} 

void accept_client(int *socket_id, fd_set *master, int *fdmax){
  struct sockaddr_in client_addr;
  socklen_t addrlen = sizeof(client_addr);
  int client_socket = accept(*socket_id, (struct sockaddr*)&client_addr, &addrlen);
  if(client_socket == -1){
    printf("accept: %s\n", strerror(errno));
  }else{
    FD_SET(client_socket, master);
    if(client_socket > *fdmax){
      *fdmax = client_socket;
    }
  }
}

int main() {
  int socket_id;
  int i;
  fd_set master, read_fds;

  setup_socket(&socket_id);
  FD_ZERO(&master);
  FD_ZERO(&read_fds);
  FD_SET(socket_id, &master);
  int fdmax = socket_id;

  while(1){
    read_fds = master;
    if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1){
      printf("select: %s\n", strerror(errno));
      exit(0);
    }
    for(i = 3; i <= fdmax; i++){
      if(FD_ISSET(i, &read_fds)){
	if(i == socket_id){
	  accept_client(&socket_id, &master, &fdmax);
	}else{
	  process(i, &master, socket_id, fdmax);
	}
      }
    }
  }

  return 0;
}
