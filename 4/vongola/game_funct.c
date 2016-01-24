#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game_funct.h"

void shuffle(player** player_list){
  // srand(time(NULL));
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
  /*----------NOTE----------
   This assumes there is always: 1 cop, 1 doc, 2 maf*/
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

int player_index(char* name, player** player_list){//find index of player
  int size=sizeof(player_list);
  int i=0;
 
  while (i<size){
    
    if (!strcmp(player_list[i]->name,name)){
      if (player_list[i]->status == ALIVE){
	return i;
      }
    }
    i++;
  }
  return -1;
}

int doctor_action(player** player_list){

  int size=sizeof(player_list);
  int i=0;
  while (i<size){
    if (player_list[i]->status == ALIVE){//if alive
     
      if (player_list[i]->role == DOCTOR){//if doctor

	int target=player_index(player_list[i]->target, player_list);//find index
	if (player_list[target]->status == DEAD){//if target is dead
	  return -1;
	}
	player_list[target]->mark=HEAL;
      }
     
    }
    i++;
  }
}

int mafia_action(player** player_list){
  int size=sizeof(player_list);
  int i=0;
  while (i<size){
  
   
    if (player_list[i]->status == ALIVE){//if alive
      if (player_list[i]->role == MAFIASO){//if mafiaso

	int target=player_index(player_list[i]->target, player_list);
	if (player_list[target]->status == DEAD){//if target is dead
	  return -1;
	}
	player_list[target]->mark=KILL;

      }
    }
    i++;
  }
}

int night_action(player** player_list){
  int size=sizeof(player_list);
  int i=0;
 
  
  if (mafia_action(player_list) < 0){//do mafia stuff
 
    return -1;
  }
 
  if (doctor_action(player_list) < 0){//do doctor stuff
    
    return -1;
  }
  while (i<size){
    if (player_list[i]->mark == KILL){
      player_list[i]->status=DEAD;
    }
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
    player_list[i]->status=ALIVE;
    player_list[i]->mark=NEUTRAL;
    i++;
  }
 
  assign_roles(player_list);
  i=0;
 
  while (i<8){
    printf("%s: %d\n", player_list[i]->name, player_list[i]->role);//prints all player names and roles in array
    i++;
  }
  printf("\n\n");
  strcat(player_list[2]->target, "Player 0");
  strcat(player_list[1]->target, "Player 2"); 
  strcat(player_list[0]->target, "Player 0");
 
  if (night_action(player_list) < 0){
    printf("Failed\n");
  }
  i=0;
 
  while (i<8){
    printf("%s: %d\n", player_list[i]->name, player_list[i]->status);
    i++;
  }
  
}
