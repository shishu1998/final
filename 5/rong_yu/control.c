#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

int server_handshake( int *from_client ){
  int to_client;
  char buffer[100];	
  mkfifo("mario", 0644);
  printf("<Server> has made the WKP 'Mario' \n");
  printf("<Server> is now waiting for a client\n");
  *from_client = open("mario", O_RDONLY); 
  read( *from_client, buffer, sizeof(buffer)) ;
  printf("<Server> connection request: [%s]\n", buffer ); //buffer is string nul  
  remove("mario");

  to_client = open( buffer, O_WRONLY);
  write(to_client, "Hi, <Server> hereby acknowledges.\n", 40);
  printf("<Server> is now connected. Yay.\n\n\n");
 
  return to_client;

}

int createClient(){
  //will make the client
  //will fork off a server and add that server file descriptor to the list
  //will add the name of the client into the same place on an array as the subserver
  printf( "Enter Name: \n");
  

  return 0;

}

int main(){
  
  signal( SIGINT, sighandler );

  int s_pipes[127];
  int to_client;
  int from_client;
  char buffer[100];
  int elder;
  int pfdR[2];
  int pfdW[2];
  while (1){
    pipe( pfdR );
    pipe( pfdW );
    to_client = server_handshake( &from_client );
    
    elder = fork();
    
    if (elder == 0){ // i.e. child
      close( pfdR[0] ); // closes read for pdfR
      close( pfdF[0] );
      //read
      while (1){
	read( from_client, buffer, sizeof(buffer));
	//printf( "<Server> received: %s\n", buffer);
	//printf( "<Server> will now encypt stuff to send back\n");
	
	char ch;
	int pos=0;
	int i=0;
	int num = 0;
	char alpha[27] = "abcdefghijklmnopqrstuvwxyz";
	
	while (buffer[i]){
	  ch = toupper(buffer[i]);
	  buffer[i] = ch;
	  i++;
	}
	buffer[i]= '?';
	buffer[i+1] = 0;
      
	//printf("<Server> will now write %s \n", buffer );
	write( to_client, buffer, sizeof(buffer));
	//printf("<SubServer> will now cycle back.\n");
      }
    } //if (i == 0)
    else{ //parent
      close (to_client);
      close (from_client);
    }
  }
}
