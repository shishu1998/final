#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>

char *str_upper(char *str); //changes the string to uppercaes
char *show_current_game(void); //returns a string that uses the true/false or space array to return underscore or the character that is guessed
char *show_char_guessed(void);
int win_lose(void); //checks if there is anything in the array that has 0, meaning that there are still characters that are not guessed
int rand_num(int divide); //random number to grab random word(server sided)

void update_current_game(char *str);
void setup_game(void);
char *print_game(void); //prints the hangman things that are needed (hangman ascii, word with holes, definition + more)



typedef struct game{
  int index_word;
  char *given_word;
  char *given_def;
  int length_word;
  int current_hangman;
  int current_game[256]; //cannot figure out a way to create dynamic array using int from same struct.. fixed by limiting using length_word
  int char_guess[26];
} hangman_t;

hangman_t game_set;


#endif
