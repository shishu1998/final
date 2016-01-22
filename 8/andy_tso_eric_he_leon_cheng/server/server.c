#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include "players.c"


void process( char *s ) {
  while ( *s ) {
    *s = (*s - 'a' + 13) % 26 + 'a';
    s++;
  }
}

static void sighandler(int signo) {
  // get rid of the annoying mario
  if (signo == SIGINT) {
    remove("mario");
    exit(0);
  }
}

int server_handshake( int *from_client ) {
  int to_client;
  char buffer[100];

  mkfifo( "mario", 0644 ); //create WKP
  *from_client = open( "mario", O_RDONLY ); //Open & wait for connect
  remove( "mario" ); //once connected, remove the pipe file

  players_connect();

  int f = fork();
  if (f == 0) {
    read( *from_client, buffer, sizeof(buffer) ); //read from client
    printf( "<server> connection established: [%s]\n", buffer );
    to_client = open(buffer, O_WRONLY);


    /* strcpy(player_ids[player_count-1],buffer); //buffer should hopefully be the pid of child */
    /* int i = 0; */
    /* /\* printf("player_ids[0]: %s, ", player_ids[0]); *\/ */
    /* /\* printf("player_ids[1]: %s, ", player_ids[1]); *\/ */
    /* /\* printf("player_ids[2]: %s, ", player_ids[2]); *\/ */
    /* while(i<desired_total){ */
    /*   printf("player_ids[%d]: %s, ", i, player_ids[i]); */
    /*   i++; */
    /* } */
    /* printf("\n"); */
  

    strncpy( buffer, "its-a-me, mario!", sizeof(buffer) );
    write( to_client, buffer, sizeof(buffer) ); //send initial message

    return to_client;
  } else {
    return 0;
  }
}


void client_connection( int to_client, int from_client ) {
  char buffer[100];

  printf("from_client: %d\n", from_client);
  printf("player_count: %d\n", player_count);
  if (from_client != 0)
    player_ids[player_count-1] = from_client;
  int i = 0;
  while(i<desired_total){
    //printf("player_ids[%d]: %d, ", i, player_ids[i]);
    i++;
  }
  printf("\n");

  printf("before client_connection while loop\n");
  while( read( from_client, buffer, sizeof(buffer) ) ) {
    printf( "<server> received [%s]\n", buffer );
    process( buffer );
    write( to_client, buffer, sizeof(buffer) ); //HERE IS WHERE YOU WRITE TO CLIENT
    
    /*********************************************************************/
    /* char foo[100] = "helllo!\n\n";					 */
    /* write( 4, foo, sizeof(foo) ); //HERE IS WHERE YOU WRITE TO CLIENT */
    /*********************************************************************/

    strncpy( buffer, "", sizeof(buffer) );
  }
}

int main() {
  signal(SIGINT, sighandler);

  ask_for_total();

  int to_client;
  int from_client;

  int i = 0;
  while(i<desired_total){
    printf("player_ids[%d]: %d, ", i, player_ids[i]);
    i++;
  }

  while (1) {   

    if(player_count<desired_total){ //stops connecting to more clients once desired_total has been reached
      printf("<server> waiting for connection\n");

      to_client = server_handshake(&from_client);

      if (to_client != 0) {
        client_connection(to_client, from_client);
        close(to_client);
      }
    }
    else{
      // printf("Game start!\n");

    }
    
  }

  return 0;
}
