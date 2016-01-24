#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void process(int fd, fd_set *master){
  char sen[256];
  char rec[256];
  int num_bytes;
  num_bytes=recv(fd,rec,sizeof(rec),0);
  if(num_bytes == -1){
    printf("recv: %s\n", strerror(errno));
    exit(0);
  }else if(num_bytes == 0){
    close(fd);
    FD_CLR(fd, master);
  }
  rec[num_bytes]='\0';
  printf("RECEIVED:%s\n", rec);
  fflush(stdout);
}

int main() {
  int socket_id;
  int i = 1;
  fd_set master, read_fds;
  
  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_id == -1){
    printf("socket: %s\n", strerror(errno));
    exit(0);
  }

  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(56347); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  if(setsockopt(socket_id, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(socket_id)) == -1){
    printf("setsockopt %s\n", strerror(errno));
    exit(0);
  }
  if(bind(socket_id, (struct sockaddr *)&listener, sizeof(listener)) == -1){
    printf("bind: %s\n", strerror(errno));
    exit(0);
  }
  
  if(listen(socket_id, 15) == -1){
    printf("listen: %s\n", strerror(errno));
    exit(0);
  }

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
    for(i = 0; i <= fdmax; i++){
      if(FD_ISSET(i, &read_fds)){
	if(i == socket_id){
	  struct sockaddr_in client_addr;
	  socklen_t addrlen = sizeof(client_addr);
	  int client_socket = accept(socket_id, (struct sockaddr*)&client_addr, &addrlen);
	  FD_SET(client_socket, &master);
	  if(client_socket > fdmax){
	    fdmax = client_socket;
	  }
	}else{
	  process(i, &master);
	}
      }
    }
  }

  return 0;
}
