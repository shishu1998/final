#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "deck.h"


static void sighandler(int signo){
  if(signo == SIGINT){
    printf("Server crash, oopsies doops\n");
    remove("pipe");
    exit(0);
  }
}


int handshake(int *from_player, card *redDeck, int *ids){
  int freeID=0;
  while(!(*ids)){
    freeID++;
  }
  int to_player;
  char buffer[100];
  int counter = 0;
  card redCards[7];
  
  mkfifo("pipe",0644);
  *from_player = open("pipe",O_RDONLY);
  remove("pipe");
  
  int pid = fork();
  if(pid == 0){
    read(*from_player,buffer,sizeof(buffer));
    printf("Handshake done\n");
    
    to_player = open(buffer,O_WRONLY);
    remove(buffer);
    write(to_player,&ids[freeID],sizeof(int));
    
      
    while (counter < 7){
      redCards[counter] = deal_redcard(redDeck);
      strcpy(buffer,redCards[counter].content);
      write(to_player,buffer,sizeof(buffer));
      counter++;
    }
    
    ids[freeID] = 0;
    return to_player;
  }
  else{
    return 0;
  }
}

void player_connection(int to_player,int from_player){
  
  char buffer[100];
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
  green_deck[pos].content = NULL;
  return green_card;
}

card deal_redcard(card* red_deck){
  int pos = 200;
  while(!(red_deck[pos].content) && pos!=746){
    pos++;
  }
  card red_card = red_deck[pos];
  red_deck[pos].content = NULL;
  return red_card;
}
//Receiving methods//
void receive_redcard(int from_player){
  char buffer[100];
  read(from_player,buffer,sizeof(buffer));
}

void receivecards(int* from_server,card *received[8]){
  char buffer[100];
  int counter = 0;
  while(counter < 8){
    read(*from_server,buffer,sizeof(buffer));
    (*received)[counter] = *makecard(buffer,"red");
    printf("%s\n",((*received)[counter]).content);
    counter ++;
  }
}

//
/*
   while(1){
    printf("select a card as the winner: \n");
    int counter = 0;
    while(counter < 8 && received[counter].content){
      printf("%d.%s\n",counter,received[counter].content);
    }
    fgets(buffer,sizeof(buffer),stdin);
    *strchr(buffer,'\n') = 0;
    int winner = atoi(buffer);
    while(winner < 0 || winner > 7 || !(received[winner].content)){
      printf("please type in a valid number: \n");
      while(counter < 8 && received[counter].content){
	printf("%d.%s\n",counter,received[counter].content);
      }
      fgets(buffer,sizeof(buffer),stdin);
      *strchr(buffer,'\n') = 0;
      int winner = atoi(buffer);
    }
    write(to_server,received[winner].content,sizeof(received[winner].content));    
  }
*/

int main(){

  signal(SIGINT,sighandler);
  

  int ids[8] = {1,2,3,4,5,6,7,8};
  int to_player;
  int from_player;
  char buffer[100];
  card* red = makedeck("red");
  card* green = makedeck("green");
  int playerturn;
  int playernum = 0;


  while(1){
    printf("waiting for players to connect\n");
    to_player = handshake(&from_player,red,ids,buffer);
    
    if(to_player != 0){
      
      player_connection(to_player,from_player);
      
      close(to_player);
    }
  }
 
  return 0;
}
