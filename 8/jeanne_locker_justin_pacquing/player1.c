#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>


//function to process clients messages                                                                                                                                               
void client_connect (int to_client, int from_client) {
  char comms[100];

  while( read(from_client, comms, sizeof(comms)) ){
      printf("Server got this: %s\n", comms);
      strcat(comms, " in this Spaghetti\n");
      write(to_client, comms, sizeof(comms) );

      strncpy(comms, "",sizeof(comms));
    }
}

int server_handshake(int *from_client){

  int to_client;
  char buff[100];

  mkfifo( "popeye", 0644 );
  from_client = open( "popeye", O_RDONLY );
  printf("At Last! My Client in shining armor\n");

  remove("popeye");
  
  read(*from_client, buff, sizeof(buff));
  printf("My Client in Shining armor is Client %s, has arrived!\n", buff);
  to_client = open( buff, O_WRONLY );
  
  strncpy( buff, "Subserver Loves You!", sizeof(buff) );
  write(to_client, buff, sizeof(buff));
   
  return to_client;
}

static void sighandler(int signo){
  if (signo == SIGINT){
    printf("\nClosing Shop\n");
    remove("popeye");
    exit(0);
  }
}

int main(){
  signal( SIGINT, sighandler );
  
  int to_client;
  int from_client;

  printf("Will a Client in shining armor complete me?\n");
  //server creates wkp
  mkfifo( "popeye", 0644 );
  //server waits for connection
  from_client = open( "popeye", O_RDONLY );
  printf("At Last! My Client in shining armor\n");
  //client does their their side of handshake
  //server recieves private pipe name
  //server removes wpk
  remove("popeye");
  
  while(1){
    //does rest of handshake: handles subservers and create new wkp's 
    to_client = server_handshake(&from_client);
  }
  return 0;
}
    
