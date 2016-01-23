#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
  char color; //1-red, 1-blue, 2-green, 3-yellow
  int value; //10-skip, 11-reverse, 12-plus two, 13-wild, 14-wild four
} card;

typedef struct
{
  int position;
  card cards[1000];
} player;


int total_players;
int current_player;
player player_list[1000];

//ANDY'S CODE STARTS HERE
// returns a card of random value and random color
srand(time(NULL));
card draw_card() {
  card new_card;
  new_card.color = rand() % 4;//[0,3]
  new_card.value = rand() % 15;//[0,14]
  return new_card;
}

// play card
void play_card(player p, card c) {
  p.cards
}
//ANDY'S CODE ENDS HERE

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
