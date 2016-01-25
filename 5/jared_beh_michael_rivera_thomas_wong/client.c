#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include "game.c"

int main(){
  char* clear = "\x1b[2J";
  char* hide =  "\x1b[?25l";
  char* show =  "\x1b[?25h";
  char* go = "\x1b[0;0H";
  int socket_id;
  char buffer[82];
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
  printf("Explanation of GAME HERE




");
  while(1){
    read(socket_id,buffer,sizeof(buffer));
    if(buffer[0]){
      break;
    }
    int i = 1;
    int c = 0;
    int q = 0;
    char outpu[612];
    while(q < 17){
      if((q % 2) == 1){
	if(((c + 1) % 4) == 0){
	  if(((c + 1) % 12) == 0){
	    outpu[c] = '=';
	  }else{
	    outpu[c] = '+';
	  }
	}else{
	  outpu[c] = '-';
	}
      }else{
	if((c % 2) == 0){
	  outpu[c] = ' ';
	}else{
	  if(((c + 1) % 12) == 0){
	    outpu[c] = '=';
	  }else if(((c + 1) % 4) == 0){
	    outpu[c] = '|';
	  }else{
	    outpu[c] = buffer[i];
	    i++;
	  }
	}
      }
      c++;
      if(c == 35){
	q++;
	c = 0;
      }
    }
  }

  /*
  printf("%s",clear);
  printf("%s",hide);
  printf("%s",show);
  printf("%s",go);
  */
  //hide,clear,go,stuff,\n,show
  return 0;
}
