#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "deck.h"

card hand[17];

void printhand(){
  int counter = 0;
  while(hand[counter].content){
    printf("%d.%s",counter,hand[counter].content);
    counter ++;
  }
}

int player_handshake(int *from_server){
  int to_server;
  char buffer[100];

  sprintf(buffer,"%d",getpid());
  mkfifo(buffer,0644);

  to_server = open("pipe",O_WRONLY);
  write(to_server,buffer,sizeof(buffer));
  
  *from_server = open(buffer,O_RDONLY);
  remove(buffer);
  
  read(*from_server,buffer,sizeof(buffer));
  printf("Player connection established: %s\n",buffer);

  return to_server;
  


}

//Card methods//
card* send_redcard(int to_server){
  char buffer[100];
  
  printf("Pick a red card (index)  to send to the server...");
  fgets(buffer,sizeof(buffer),stdin);
  *strchr(buffer,'\n') = 0;
  int index  = atoi(buffer);
  if (index >= 0 || index <= 7){
    write(to_server,buffer,sizeof(buffer));
    printf("You sent: %s\n", hand[index].content);
  }
  else{
    printf("You did not enter a legal number");
  }
  
}
///////////


//Judge methods//
void pick_winning_card(card* pile, int from_server, int to_server){
  char buffer[100];
  
  printf("Pick what you think best fits the adjective...");
  read(from_server,buffer,sizeof(buffer));
  printf("Here is the list of cards received...");
  int counter = 0;                                                                
  while(pile[counter].content){                                                  
    printf("%d.%s",counter,hand[counter].content);                               
    counter ++;                                                                  
  }
  fgets(buffer,sizeof(buffer),stdin);
  *strchr(buffer,'\n') = 0;
  int index  = atoi(buffer);
  if (index >= 0 || index <= 2){ //assuming there are 3 players
    write(to_server,buffer,sizeof(buffer));
    printf("You chose: %s\n", pile[index].content);
  }
  else{
    printf("You did not enter a valid index");
  }
}




int main(){
  
  int to_server;
  int from_server;
  char buffer[100];
  
  to_server = player_handshake(&from_server);
  while(1){
    printhand();
    printf("type something: ");
    fgets(buffer,sizeof(buffer),stdin);
    *strchr(buffer,'\n') = 0;
    write(to_server,buffer, sizeof(buffer));
    read(from_server,buffer,sizeof(buffer));
    printf("Player received: %s\n",buffer);
    
  }
  
  close(to_server);
  close(from_server);
  return 0;
}
