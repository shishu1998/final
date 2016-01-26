#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

#include "hangman.h"

int shandshake(int *from_client){
  int to_client;
  char buffer[1024];

  mkfifo("HANGMAN", 0644);
  *from_client = open("HANGMAN", O_RDONLY);
  
  remove("HANGMAN");
  read(*from_client, buffer, sizeof(buffer));

  printf("Client: %s\n", buffer);
  to_client = open(buffer, O_WRONLY);

  strncpy(buffer, "Connected", sizeof(buffer));
  write(to_client, buffer, sizeof(buffer));

  return to_client;
}

static void sighandler(int signo){
  if(signo == SIGINT){
    remove("HANGMAN");
    exit(0);
  }
}

int main(){

  //creating own word/clue
  int WORD_CAP = 1024;
  char word[WORD_CAP];
  printf("\nWord: ");
  fgets(word, WORD_CAP, stdin);
  if(word[strlen(word)-1] == '\n')
    word[strlen(word)-1] = '\0';

  char clue[WORD_CAP];
  printf("\nClue: ");
  fgets(clue, WORD_CAP, stdin);
  if(clue[strlen(clue)-1] == '\n')
    clue[strlen(clue)-1] = '\0';

  setup_game(word, clue);
  //connection stuff

  printf("\n\n");
  signal(SIGINT, sighandler);
  //setup_game();

  int to_client;
  int from_client;

  while(1){
    printf("Waiting\n");
    to_client = shandshake(&from_client);
    char buffer[1024];
    write(to_client, print_game(), sizeof(print_game()));
    while(read(from_client, buffer, sizeof(buffer))){
      if(game_set.current_hangman < 7){
	printf("Guesser guessed: %s\n", buffer);
	update_current_game(buffer);
	printf("%s\n", print_game());
	strncpy(buffer, print_game(), sizeof(buffer));
	write(to_client, buffer, sizeof(buffer));
	strncpy(buffer, "", sizeof(buffer));
      }
      else if(win_lose() == 1){
	write(to_client, "You win!", sizeof("You win!"));
	printf("Client wins!");
	close(to_client);
      }
      else if(game_set.current_hangman > 6){
	write(to_client, "You lose!", sizeof("You lose!"));
	printf("Client is a loser ;)");
	close(to_client);
      }
    }
    close(to_client);
  }
  return 0;
}
  
