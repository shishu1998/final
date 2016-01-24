#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void sighandler(int signo){
  int error;
  if (signo==SIGPIPE){
    error=close(socket_id);
    if (error == -1)
	perror("Error closing client socket\n");
    printf("Server disconnected, client exiting\n");
    exit(42);
  }
  if (signo==SIGINT){
    write(socket_id,&kill_num,4);
    printf("Closing socket\n");
    error=close(socket_id);
    if (error == -1)
      perror("Error closing socket\n");
    printf("Socket closed\n");
    exit(42);
  }
}

int connect_server(){
  struct sockaddr_in sock; 
  int socket_id = socket(AF_INET, SOCK_STREAM, 0);
  sock.sin_family = AF_INET; //socket type to IPv4
  sock.sin_port = htons(PORTNUM); //port # 
  //convert IP address to correct format and insert into sock.sin_addr
  inet_aton( "127.0.0.1", &(sock.sin_addr) ); 
  //insert the socket info stuff into the file thing
  bind(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  //attempt a connection. Will return -1and set errno if failed
  int error = connect( socket_id, (struct sockaddr *)&sock, sizeof(sock));
  if (error==-1){
    printf("Error connecting to server: %s\n",strerror(errno));
    exit(42);
  }
  return socket_id;
}

int main(int argc, char **argv) {

  int socket_id;
  char buffer[256];
  int i;
  int exit_status = 0;
  
  while(exit_status < 10){
    //create the socket
    socket_id = socket( AF_INET, SOCK_STREAM, 0 );
    
    //bind to port/address
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;   
    sock.sin_port = htons(6001);
    //Set the IP address to connect to
    //127.0.0.1 is the "loopback" address of any machine
    inet_aton( "127.0.0.1", &(sock.sin_addr) );
    bind( socket_id, (struct sockaddr *)&sock, sizeof(sock));
    
    //attempt a connection
    i = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
    printf("<client> connect returned: %d\n", i);
    
    
    read( socket_id, buffer, sizeof(buffer));
    printf("<client> received: [%s]\n", buffer );
    exit_status ++;
    //if (buffer == "exit")
    //exit_status = 11;
  }
  
  exit_status = 0;
  
  return 0;
}
