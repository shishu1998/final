#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  char color;
  int value; //s-skip, r-reverse, t-plus two, w-wild, f-wild four
} card;

typedef struct
{
  int position;
  card cards[1000];
} player;


int total_players;
int current_player;
player player_list[1000];

//Note: Skip and Reverse are to be dealt with later
void next_player(){
  player players[ total_players ];

  if ( current_player >= total_players )
    current_player = 0;
  else
    current_player++;
}

void add_player(player p){
  player_list[ current_player ] = p;
}



int desired_total;
int player_count;
//char player_ids[100][100];
int player_ids[100];

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
