#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

int ships[5] = {0, 0, 0, 0, 0};

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


/*======== int makeFleet() ==========
Inputs: 
int place: user's inputted placement of a ship
int places[]: array holding all ship places

Result:
fills up places[] with user's inputs (sets coordinates of ships)

====================*/
int makeFleet(){

  int pos;
  
  printf("Input where you want your first ship! Each ship is one unit.\nDon't use any spaces between the numbers: ");
  scanf("%d", &pos);
  ships[0] = pos;
  printf("Input your second location: ");
  scanf("%d", &pos);
  ships[1] = pos;
  printf("Your third: ");
  scanf("%d", &pos);
  ships[2] = pos;
  printf("Your fourth: ");
  scanf("%d", &pos);
  ships[3] = pos;
  printf("And your fifth: ");
  scanf("%d", &pos);
  ships[4] = pos;
}

/*======== int dontBreak()  ==========

check to see is 11-15, 21-25, 31-35, 41-45, 51-55
also cehck to see no double entries
Inputs: 


Result:
makes it harder for someone to break our program
if okay = 0, then there's a problem.

====================*/
int dontBreak(int pos){
  int okay = 0;
  //check to see within range
  
  if ( ((pos > 10)&&(pos < 16)) ||
       ((pos > 20)&&(pos < 26)) ||
       ((pos > 30)&&(pos < 36)) ||
       ((pos > 40)&&(pos < 46)) ||
       ((pos > 50)&&(pos < 56)) ){
    okay = 1;
  }

  //check to see no double entries
  if (pos == ships[0] ||
      pos == ships[1] ||
      pos == ships[2] ||
      pos == ships[3] ||
      pos == ships[4]){
    okay = 0;
  }

  return okay;
}

int main(){

  signal( SIGINT, sighandler );
  
  //establish game parameters
  //function for choosing player setting (ship placements, etc.)
  //handshake to establish connection with Player 2

  makeFleet();
  
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
    
