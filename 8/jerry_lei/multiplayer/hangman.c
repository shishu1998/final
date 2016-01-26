#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

#include "hangman.h" //header file containing the words and the hangman ascii values from 0-6. words[0-20], definitions[0-20], hangman_numbers[0-6], max_words for cap and rand_num


char *hangman_numbers[7] = {
"\
\n\t +---+\
\n\t |   |\
\n\t     |\
\n\t     |\
\n\t     |\
\n\t     |\
\n\t========\n", 

"\
\n\t +---+\
\n\t |   |\
\n\t O   |\
\n\t     |\
\n\t     |\
\n\t     |\
\n\t========\n",

"\
\n\t +---+\
\n\t |   |\
\n\t O   |\
\n\t |   |\
\n\t     |\
\n\t     |\
\n\t========\n",

"\
\n\t +---+\
\n\t |   |\
\n\t O   |\
\n\t/|   |\
\n\t     |\
\n\t     |\
\n\t========\n",

"\
\n\t +---+\
\n\t |   |\
\n\t O   |\
\n\t/|\\  |\
\n\t     |\
\n\t     |\
\n\t========\n",

"\
\n\t +---+\
\n\t |   |\
\n\t O   |\
\n\t/|\\  |\
\n\t |   |\
\n\t/    |\
\n\t========\n",

"\
\n\t +---+\
\n\t |   |\
\n\t O   |\
\n\t/|\\  |\
\n\t |   |\
\n\t/ \\  |\
\n\t========\n"

};


void setup_game(char *word, char *clue){
  game_set.current_hangman = 0;
  
  //  game_set.index_word = rand_num(max_words);
  game_set.given_word = str_upper(word);//str_upper(words[game_set.index_word]);
  game_set.given_def = clue;//definitions[game_set.index_word];
  
  game_set.length_word = strlen(game_set.given_word);


  int c1 = 0;
  while(c1 < game_set.length_word){
    if(game_set.given_word[c1] == ' ')
      game_set.current_game[c1] = 2;
    if(game_set.given_word[c1] != ' ')
      game_set.current_game[c1] = 0;
    c1++;
  }
  c1 = 0;
  while(c1 < 26){
    game_set.char_guess[c1] = 0;
    c1++;
  }
}

char *print_game(void){ //this malloc needs to be freed.
  char *return_string = malloc(1024);
  strcpy(return_string, "");
  strcat(return_string, hangman_numbers[game_set.current_hangman]);

  char *s2 = show_current_game();
  strcat(return_string, s2);
  free(s2);
  
  char *s3 = show_char_guessed();
  strcat(return_string, "\n\t\t");
  strcat(return_string, s3);
  free(s3);

  char *s4 = game_set.given_def;
  strcat(return_string, "\n\t");
  strcat(return_string, s4);
  return return_string;

}


int rand_num(int DIVIDE){
  int c = open("/dev/urandom", O_RDONLY);
  unsigned int num;
  read(c, &num, 4);
  close(c);
  return num % DIVIDE;
}

char *str_upper(char *str){
  char *str2 = malloc(strlen(str)+1);
  int c1 = 0;
  while(c1 < strlen(str)){
    str2[c1] = toupper(str[c1]);
    c1++;
  }
  str2[c1] = '\0';
  return str2;
}
  

char *show_current_game(void){
  int c1 = 0;
  char return_string[1024] = "\t";
  int c2 = 1;
  while(c1 < game_set.length_word){
    if(game_set.current_game[c1] == 0){
      return_string[c2] = ' ';
      return_string[c2+1] = '_';
    }
    if(game_set.current_game[c1] == 1){
      return_string[c2] = ' ';
      return_string[c2+1] = game_set.given_word[c1];      
    }
    if(game_set.current_game[c1] == 2){
      return_string[c2] = '\n';
      return_string[c2+1] = '\t';
    }
    c1++;
    c2+=2;
  }
  char *result = malloc(c2 + 1);
  strncpy(result, return_string, c2);
  return result;
}

char *show_char_guessed(void){
  int c1 = 0;
  char return_string[1024] = "\tCharacters Guessed:";
  int c2 = 20; //length of return_string at this point
  while(c1 < 26){
    if(game_set.char_guess[c1] == 1){
      char char_show = c1 + 65;
      return_string[c2] = ' ';
      return_string[c2+1] = char_show;
      c2+=2;
    }
    c1++;
  }
  char *result = malloc(c2+1);
  strncpy(result, return_string,c2);
  return result;
}

int win_lose(void){ //checks if current_game has any fails, returns 0 if game is not won, returns 1 if game is won (everything in current_game is 1
  if(game_set.current_hangman == 7)
    return 2;
  int c1 = 0; 
  while(c1 < game_set.length_word){
    if(game_set.current_game[c1] == 0)
      return 0;
    c1++;
  }
  return 1;
}
  
void update_current_game(char *str){ //changes the game_set.current_game by checking if str has is only 1 char, or matches the game_set.given_word. If it is longer than 1, does not check and does not add to game_set.current_hangman. 
  if(strlen(str) == game_set.length_word){ //game finished
    if(strcmp(str_upper(str), game_set.given_word) == 0){
      int c1 = 0;
      while(c1 < game_set.length_word){
	game_set.current_game[c1] = 1;
	c1++;
      }
    }
    else
      game_set.current_hangman++;
    return;
  }
  if(strlen(str) == 1){ //guess 1 character
    char j = toupper(str[0]);
    if(j == ' ') //space is not a letter that can be guessed
      return;
    if(game_set.char_guess[j-65] == 1) //character has been guessed before
      return;
    if(game_set.char_guess[j-65] == 0){
      game_set.char_guess[j-65] = 1;
      int c1 = 0;
      int yes_no = 0;
      while(c1 < game_set.length_word){
	if(game_set.given_word[c1] == j){
	  game_set.current_game[c1] = 1;
	  yes_no++;
	}
	c1++;
      }
      if(yes_no > 0)
	return;
      if(yes_no == 0){
	game_set.current_hangman++;      
	return;
      }
    }
  }
}
      


/*
int main(){
  setup_game();
  printf("%s",print_game());
  /*  char *funtimes = "funTiMES";
  printf("\nLower: %s", funtimes);
  funtimes = str_upper(funtimes);
  printf("\nUpper: %s\n", funtimes);
  */
  /*
  update_current_game("m");
  print_game();
  update_current_game("R");
  print_game();
  update_current_game("c");
  print_game();
  update_current_game("MaJorIty RuLe");
  print_game();
  

  printf("\n\n");
  return 0;
}
  */


