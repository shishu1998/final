#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

//semaphore will control who's turn it is
//player will have to wait for sempahore access to be given to program before being prompted by program

//performs game functions
//will recieve info on own/player 2 attacks and adjust board accordingly
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
  *from_client = open( "popeye", O_RDONLY );
  printf("At Last! My Client in shining armor\n");

  remove("popeye");
  
  read(*from_client, buff, sizeof(buff));
  printf("My Client in Shining armor is Client %s, has arrived!\n", buff);
  to_client = open( buff, O_WRONLY );
  
  strncpy( buff, "Server Loves You!", sizeof(buff) );
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
  
  //establish game parameters
  //function for choosing player setting (ship placements, etc.)
  //handshake to establish connection with Player 2
  
  int to_client;
  int from_client;
  while(1){
    printf("Will a Client in shining armor complete me?\n");
    to_client  = server_handshake(&from_client);

    client_connect( to_client, from_client);

    close( to_client);
  }

  return 0;
}
    
