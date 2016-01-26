//server side of making a TCP (with a 3 way handshake)

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){
  int socket_id, socket_client,pid;
  char buffer[256];
    
    
  //create the socket
  socket_id = socket(AF_INET, SOCK_STREAM, 0);
 
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;
  listener.sin_port = htons(5000); 
  listener.sin_addr.s_addr = INADDR_ANY; // bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
    
  listen(socket_id, 1);//opens the socket up for a connection
  printf("<server> listening\n");
    
  for ( ; ; ){

    socket_client = accept(socket_id, NULL, NULL);
    printf("<server> connected: %d\n", socket_client);
    
    if ( (pid = fork()) == 0 ){
      while(1){
	recv(socket_client, buffer, sizeof(buffer), 0);
	printf("<server> Recieved:[%s]\n", buffer);
	strtok(buffer, "\n");
	send(socket_client, buffer, sizeof(buffer), 0); //FOR INT STUFFS WE JUST HAVE TO GET THAT AS A VARIABLE AND FUCKING SEND THAT SHIT HERE
      }
    }
    else{
      close(socket_client);
    }
  }
  return 0;
}
