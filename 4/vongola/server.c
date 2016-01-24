#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void process(int fd, fd_set *master, int fdmax, int socket_id, char*** ulist){
  char sen[256];
  char rec[256];
  char line[256];
  int num_bytes;
  int new_player = 0;
  printf("Status:%s\n",(*ulist)[fd]);
  num_bytes=recv(fd,rec,sizeof(rec),0);
  if(num_bytes == -1){
    printf("recv: %s\n", strerror(errno));
    exit(0);
  }else if(num_bytes == 0){
    close(fd);
    FD_CLR(fd, master);
  }
  rec[num_bytes]='\0';
  if(strlen((*ulist)[fd])==0){
    char *name = (char*)malloc(sizeof(char));
    strcpy(name,rec);
    (*ulist)[fd]=name;
    new_player=1;
  }
  int i;
  for (i=0; i<=fdmax; i++){
    if (FD_ISSET(i,master)&&i!=socket_id){
      printf("Name Changed: %s\n",(*ulist)[fd]);
      //printf("works\n");
      if(!new_player){
	//printf("works2\n");
	strcpy(line,(*ulist)[fd]);
	strcat(line,": ");
	strcat(line,rec);
	printf("Has A Name: %d\n",strlen((*ulist)[fd]));
	if(send(i,line,strlen(line),0)==-1)
	  printf("SEND: %s\n",strerror(errno));
      }
      else{
	/*char *name = (char *)malloc(sizeof(char));
	strcpy(name,rec);
	(*ulist)[fd]=name;*/
	strcpy(line,(*ulist)[fd]);
	strcat(line," has entered the town.\n");
	//printf("%s",line);
	if(send(i,line,strlen(line),0)==-1)
	  printf("SEND: %s\n",strerror(errno));
      }
    }
  }
}

int main() {
  int socket_id;
  int i;
  fd_set master, read_fds;
  char **ulist = (char**)malloc(10*sizeof(char*));
  for(i = 0; i < 10; i++)
    ulist[i]="";
  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_id == -1){
    printf("socket: %s\n", strerror(errno));
    exit(0);
  }

  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(56348); //port #
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
	//printf("%d\n",i);
	if(i == socket_id){//i==3
	  struct sockaddr_in client_addr;
	  socklen_t addrlen = sizeof(client_addr);
	  int client_socket = accept(socket_id, (struct sockaddr*)&client_addr, &addrlen);
	  FD_SET(client_socket, &master);
	  char * greeting = "Welcome to Vongola, a modified Mafia in C!\n";
	  send(client_socket, greeting, strlen(greeting),0);
	  if(client_socket > fdmax){
	    fdmax = client_socket;
	  }
	}else{
	  process(i, &master, fdmax, socket_id, &ulist);
	}
      }
    }
  }

  return 0;
}
