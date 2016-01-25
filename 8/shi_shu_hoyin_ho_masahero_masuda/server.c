#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "deck.h"

int connectedPlayers = 0;
int ids[8] = {1,2,3,4,5,6,7,8};

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("Server crash, oopsies doops\n");
    remove("pipe");
    exit(0);
  }
}

int handshake(int *from_player, card *redDeck, card *greenDeck){
  int freeID=0;
  while(!(*ids)){
    freeID++;
  }
  printf("Ho Yin Ho\n");
  int to_player;
  char buffer[100];
  int counter = 0;
  card redCards[7];
  card greenCard = deal_greencard(greenDeck);

  printf("Ho Yin went black\n");
  mkfifo("pipe",0644);
  *from_player = open("pipe",O_RDONLY);
  printf("Now Ho Yin can't go back\n");
  remove("pipe");
  connectedPlayers += 1; 
  
  int f = fork();
  if(f == 0){
    read(*from_player,buffer,sizeof(buffer));
    printf("Handshake done\n");
    
    to_player = open(buffer,O_WRONLY);
    remove(buffer);
    while (counter < 7){
      redCards[counter] = deal_redcard(redDeck);
      redCards[counter].owner=ids[freeID];
      counter++;
    }
    greenCard.owner=ids[freeID];
    printf("Masa is slacking\n");
    write(to_player,&ids[freeID],sizeof(int));
    ids[freeID] = 0;
    write(to_player,&redCards,sizeof(card)*7);
    printf("Masa likes Sandy\n");
    write(to_player,&greenCard,sizeof(card));
    printf("I like Sandy, Kappa\n");
    return to_player;
  }
  else{
    return 0;
  }
}

void player_connection(int to_player,int from_player){
  
  char buffer[100];
  printf("before while loop\n");
  while(read(from_player,buffer,sizeof(buffer))){
    printf("server received %s\n",buffer);
    write(to_player,buffer,sizeof(buffer));
    strncpy(buffer,"",sizeof(buffer));
  }
}
//Card Deal methods
card deal_greencard(card* green_deck){
  int pos = 0;
  while(!(green_deck[pos].content) && pos!= 250){
    pos++;
  }
  card green_card = green_deck[pos];
  green_deck[pos] = 0;
  return green_card;
}

card deal_redcard(card* red_deck){
  int pos = 200;
  while(!(red_deck[pos].content) && pos!=746){
    pos++;
  }
  card red_card = red_deck[pos];
  red_deck[pos] = 0;
  return red_card;
}
//Receiving methods//
void receive_redcard(int from_player){
  char buffer[100];
  read(from_player,buffer,sizeof(buffer));
}
//

int main(){

  signal(SIGINT,sighandler);
  
  int to_player;
  int from_player;
  char buffer[100];

  card* red = makedeck("red");
  card* green = makedeck("green");
  int playerturn;
  int playernum = 0;

  while(1){
    printf("waiting for players to connect\n");
    to_player = handshake(&from_player,red,green);
    
    if(to_player != 0){
      
      player_connection(to_player,from_player);
      
      close(to_player);
    }
  }
  
  return 0;
}
