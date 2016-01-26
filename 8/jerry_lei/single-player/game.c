#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "hangman.h"

int main(){
  setup_game();
  while(1){
    if (game_set.current_hangman < 7){
      int LINE_CAP = 1024;
      char line[LINE_CAP];
      printf("%s", print_game());
      printf("\nEnter guess (single char or full word): ");
      fgets(line, LINE_CAP, stdin);
      if(line[strlen(line) - 1] == '\n')
	line[strlen(line) - 1] = '\0';
      char *receive_line = line;
      if(strcmp(receive_line, "exit") == 0)
	exit(0);
      update_current_game(receive_line);
    }
    else if(win_lose() == 1){
      printf("%s", print_game());
      printf("You win.\n");
      exit(0);
    }
    else if(game_set.current_hangman > 6){
      printf("%s", print_game());
      printf("You lost.\n");
      exit(0);
    }
  }
  return 0;
}
	
