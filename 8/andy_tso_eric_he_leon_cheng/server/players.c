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
  int num_cards;//number of cards in player's hand
} player;


int total_players;
int current_player;
player player_list[1000];
card top_card;

//ANDY'S CODE STARTS HERE//
/*
  List of functions:
  draw_card() - returns card of random value and random color
  play_card(player p, card c) - check if card is valid, remove card from 
    player p's hand, change top card (uses the update_top_card() function)
  update_top_card( card c ) - changes top_card to c
  num_cards() - returns int, number of cards left in a player's hand
  player_action() - uses fgets to get player input
  
 */
srand(time(NULL));
card draw_card() {
  card new_card;
  new_card.color = rand() % 4;//[0,3]
  new_card.value = rand() % 15;//[0,14]
  return new_card;
}

update_top_card( card c ) {
  top_card.color = c.color;
  top_card.value = c.value;
}

int num_cards(player p) {
  
}

void play_card(player p, card c) {
  //check if this is a valid next card to play
  //if (check if card is valid) {
  //remove card from p.cards
  //change the card that is on top of the pile (shared memory?)
  //}
  //else {
  //ask player for another card to play
  //play_card(p, c);
  //}
  next_player();
}
//ANDY'S CODE ENDS HERE//

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
