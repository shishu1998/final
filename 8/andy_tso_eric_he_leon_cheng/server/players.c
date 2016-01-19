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


void player_order(){

}
