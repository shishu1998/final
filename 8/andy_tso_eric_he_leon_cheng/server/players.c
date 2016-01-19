#include <stdio.h>
#include <stdlib.h>

struct card
{
  char color;
  int value; //s-skip, r-reverse, t-plus two, w-wild, f-wild four
}

struct player
{
  int position;
  card cards[1000];
}

int total_players;
int current_player;

//Note: Skip and Reverse are to be dealt with later
void next_player(){
  player players[ total_players ];

  if ( current_player >= total_players )
    current_player = 0;
  else
    current_player++;
}
