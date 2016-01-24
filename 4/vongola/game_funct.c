#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game_funct.h"

void shuffle(player** player_list){
  srand(time(NULL));
  int size=sizeof(player_list);
 
  int interval=0;

  while (interval<size){
    int lucky=rand()%(size-interval)+interval;
    player* temp;
    temp=player_list[interval];
    player_list[interval]=player_list[lucky];
    player_list[lucky]=temp;
    interval++;
    
  }
}

void assign_roles(player** player_list){
  int size=sizeof(player_list);
  
  shuffle(player_list);
 
 
  int* roles=malloc(8);
  
  roles[0]=1;
  roles[1]=1;
  roles[2]=2;
  roles[3]=3;
 
  int i=4;

  while (i < size){
   
  
    roles[i]=0;
    i++;
  }

  i=0;
 
  while (i < size){
   
   
    player_list[i]->role=roles[i];
    i++;
  }

}

int lynch_count( int i ){
  return i/2 + 1;
}

int main(){
  player** player_list=malloc(256);
 
  int i=0;
  while (i<8){
    player_list[i]=(player*)malloc(sizeof(player));
    char temp[256];
    sprintf(temp, "Player %d", i);//testing
    strcat(player_list[i]->name, temp);
    i++;
  }
 
  assign_roles(player_list);
  printf("hello\n");
  i=0;
  while (i<8){
    printf("%s: %d\n", player_list[i]->name, player_list[i]->role);
    i++;
  }
}
