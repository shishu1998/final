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

int desired_total;
int player_count;
char player_ids[100];

void ask_for_total(){
  player_count = 0;

  printf("<server> How many players? ");
  scanf ("%d",&desired_total);
  printf("desired_total: %d\n", desired_total);
}

void players_connect(){
  player_count++;
  if (player_count==desired_total){
    printf("Desired total has been reached!\n\n");
  }
  printf("a player has joined\n");
  printf("players connected: %d\n", player_count);
}


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

    strncpy( buffer, "its-a-me, mario!", sizeof(buffer) );
    write( to_client, buffer, sizeof(buffer) ); //send initial message

    return to_client;
  } else {
    return 0;
  }
}


void client_connection( int to_client, int from_client ) {
  char buffer[100];
  printf("before client_connection while loop\n");
  printf("to_client: %d\n", to_client);
  printf("from_client: %d\n", from_client);
  player_ids[from_client/3]=(char *)from_client;
  printf("player_ids: %s\n", player_ids);
  while( read( from_client, buffer, sizeof(buffer) ) ) {
    printf( "<server> received [%s]\n", buffer );
    process( buffer );
    write( to_client, buffer, sizeof(buffer) ); //HERE IS WHERE YOU WRITE TO CLIENT
    strncpy( buffer, "", sizeof(buffer) );
  }
}

int main() {
  signal(SIGINT, sighandler);

  ask_for_total();

  int to_client;
  int from_client;

  while (1) {
    if(player_count<desired_total){ //stops connecting to more clients once desired_total has been reached
      printf("<server> waiting for connection\n");
      
      to_client = server_handshake(&from_client);
      
      if (to_client != 0) {
	client_connection(to_client, from_client);
	close(to_client);
      }
    }
  }

  return 0;
}
