#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "game.c"


int main(){
int socket_id;
board buffer[81];
int i;
int addrs;
char *server_ip;

struct sockaddr_in sock;
sock.sin_family = AF_INET;
sock.sin_port = htons(24600);
inet_aton(server_ip,&(sock.sin_addr));
bind(socket_id,(struct sockaddr*)&sock,sizeof(sock));
i=connect(socket_id,(struct sockaddr*)&sock,sizeof(sock));
printf("Connected to socket:%d",i);
read(socket_id,buffer,sizeof(buffer);

return 0;
}
