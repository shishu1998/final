#ifndef DEALER_H
#define DEALER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

typedef struct card {
  int value;
  int is_ace;
  char* name;
  
  struct card* next_card;
} card; 

#endif

/* --------------------------
Makes individial card

Input: Value (Ace is one by default), String name, is_ace (0 or 1)

Output: Pointer to card struct

*/
card* make_card( int value, char* name, int is_ace, card* c);


/* ------------------------------------
Generates deck of standard playing cards (52 unique cards, A-K, four suits) for use during gameplay
Only run once when starting new games (in main)

 - Deck is a linked list referenced through the "first card" of the linked list. 

 - Loops through value-suit (e.g. Ace of Diamonds, Ace of Clubs... King of Hearts, King of Diamonds)

 - Last card of deck points to null

Input: First card, declared in main
Output: Array of card structs referenced through the master array "deck"
*/
void make_deck( card* deck); 



/* ---------------------------------------------
Initates game and gives player and dealer cards

Input: players array, dealer being at index 0, deck, and number of players
Returns: Number of cards
*/
int deal( card* players, int number_of_cards, card* deck, int number_of_players ); 



/* ---------------------------------------
Get random card from deck and remove it from the deck, using random( <total number of current deck cards)

Input: "deck": first card of the deck (linked list)
Output: Random card struct
*/
card* random_card( card* deck, int number_of_cards ); 


/* -----------------------
Hits the player at player_index (0 == dealer) with a card

Input: players array, number of cards, the deck linkedlist, player_index (player #1, #2, etc.)
Output: card given
*/
card* hit( card* players, int number_of_cards, card* deck, int player_index );


/* ---------------------------------------
Stops the player's turn and moves on to the next player
If it is dealer's turn, end_game will be called

Input:
Output: Player number (0 == dealer)
*/
int stand( int number_of_players, int player_index );

/* ---------------------------------------
Calculates and returns dealer's score

Input: players linked list
Output: The Score (total value of cards)
 */
int dealer_score( card* players );

/* ------------------------------
Calculates and returns player's score

Input: player and player_index
Output: that player's score
*/
int player_score( card* players, int player_index );


/* --------------------------------------
Dealer stops and finishes game.

Input: The highest score from among the players
Output: Game over status and result, as dealer is last to play
*/
void end_game( int highest_player_score, int dealer_score );
