#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "deck.h"

card green_hand[8];
card red_hand[7];
int id;

int player_handshake(int *from_server){
  printf("Ho Yin IS gay\n");
  int to_server;
  char buffer[100];

  sprintf(buffer,"%d",getpid());
  mkfifo(buffer,0644);
  printf("Ho Yin IS gay\n");
  to_server = open("pipe",O_WRONLY);
  write(to_server,buffer,sizeof(buffer));
  printf("Ho Yin IS gay\n");
  printf("%s\n",buffer);
  *from_server = open(buffer,O_RDONLY);
  remove(buffer);
  printf("Ho Yin IS definitely Gay\n");
  read(*from_server,red_hand,sizeof(card)*7);
  printf("Ho Yin likes ma dick\n");
  read(*from_server,green_hand,sizeof(card));
  printf("Ho Yin thinks he's straight\n");
  read(*from_server,&id,sizeof(int));
  printf("Player connection established: %s\n",buffer);

  return to_server;
  


}

//Card methods//
void send_redcard(int to_server){
  printf("ho yin sucks dick\n");
  char buffer[100];
  int i = 0;
  while(i < 7){
    printf("%d.%s\n",i,red_hand[i].content);
    i++;
  }
  printf("Pick a red card (index)  to send to the server...\n");
  fgets(buffer,sizeof(buffer),stdin);
  *strchr(buffer,'\n') = 0;
  int index = atoi(buffer);
  if (index >= 0 && index <= 6){
    write(to_server,&red_hand[index],sizeof(red_hand[index]));
    printf("You sent: %s\n", red_hand[index].content);
  }
  else{
    printf("You did not enter a valid index\n");
  }
  
}

void send_greencard(int to_server){
  char buffer[100];
  int i = 0;
  while (i < 8){
    printf("%d.%s\n",i,green_hand[i].content);
    i++;
  }
  printf("Pick a green card (index)  to send to the server...\n");
  fgets(buffer,sizeof(buffer),stdin);
  *strchr(buffer,'\n') = 0;
  int index = atoi(buffer);
  if (index >= 0 && index <= 7){
    write(to_server,&green_hand[index],sizeof(green_hand[index]));
    printf("You sent: %s\n", green_hand[index].content);
  }
  else{
    printf("You did not enter a valid index\n");
  }
}
///////////


//Judge methods//
void pick_winning_card(card* pile, int from_server, int to_server){
  char buffer[100];
  
  printf("Pick what you think best fits the adjective...\n");
  read(from_server,buffer,sizeof(buffer));
  printf("Here is the list of cards received...\n");
  int counter = 0;                                                                
  while(pile[counter].content){                                                  
    printf("%d.%s",counter,pile[counter].content);                               
    counter ++;                                                                  
  }
  fgets(buffer,sizeof(buffer),stdin);
  *strchr(buffer,'\n') = 0;
  int index  = atoi(buffer);
  if (index >= 0 || index <= 2){ //assuming there are 3 players
    write(to_server,&pile[index],sizeof(pile[index]));
    printf("You chose: %s\n", pile[index].content);
  }
  else{
    printf("You did not enter a valid index\n");
  }
}




int main(){
  
  int to_server;
  int from_server;
  char buffer[100];
  
  to_server = player_handshake(&from_server);
  while(1){
    send_redcard(to_server);
    //send_greencard(to_server);
    printf("type something: ");
    fgets(buffer,sizeof(buffer),stdin);
    *strchr(buffer,'\n') = 0;
    write(to_server,buffer, sizeof(buffer));
    read(from_server,buffer,sizeof(buffer));
    printf("Player received: %s\n",buffer);
  }
  /*
  int i = 0;
  while(i<7){
    printf("%d.%s\n",i,red_hand[i].content);
    i ++;
  }
  while(i < 8){
    printf("%d.%s\n",i,green_hand[i].content);
    i ++;
    } */
  close(to_server);
  close(from_server);
  return 0;
}
