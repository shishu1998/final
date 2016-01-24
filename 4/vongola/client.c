#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

void process(int fd, int sockfd, char * name){
  char sen[256];
  char rec[256];
  int num_bytes;
  //printf("started processing...\n");
  if (fd==0){//send
    if(strlen(name)>0){
      //printf("HERE\n");
      //printf("|%s|: ",name);
      fgets(sen,sizeof(sen),stdin);
      send(sockfd,sen,strlen(sen),0);
    }
  }else{//receive
    //printf("HERE1\n");
    num_bytes=recv(sockfd,rec,sizeof(rec),0);
    if(num_bytes==-1){
      printf("recv: %s\n",strerror(errno));
      exit(0);
    }
    else if(num_bytes==0){
      exit(0);
    }
    rec[num_bytes]='\0';
    if (strlen(name)==0){//if user still has not made a name
      printf("Please enter your desired name: ");
      fgets(sen,sizeof(sen),stdin);
      send(sockfd,sen,strlen(sen)-1,0);
      strncpy(name,sen,strlen(sen)-1);
    }
    printf("%s",rec);
    fflush(stdout);
  }
}

int main(int argc, char **argv) {

  int socket_id, fdmax;
  char buffer[256];
  int i;
  fd_set master;
  fd_set read_fds;
  char name[15]="";
  char *n = name;
  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_id == -1){
    printf("socket: %s\n", strerror(errno));
    exit(0);
  }

  //bind to port/address
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(56348);
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
    if(strlen(name)!=0){
      if (select(fdmax+1, &read_fds, NULL, NULL, NULL)==-1){
	printf("select: %s\n", strerror(errno));
      }
    }
    for (i=0;i<=fdmax;i++){
      //printf("works2\n");
      if (FD_ISSET(i, &read_fds)){
      //printf("%d, %d\n",i,fdmax);
	process(i,socket_id,n);
	//printf("here\n");
      }
    }
  }

  return 0;
}
