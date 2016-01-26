#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "client_relations.h"

void reset_game() {
  int f = open("game.txt", O_CREAT | O_WRONLY, 0666);
  char board [6][7];
  int r = 0;
  int c = 0;
  for (;r < 6; r++) {
    for (c = 0; c < 7; c++) {
      board[r][c] = 'O';
    }
  }
  write(f, &board, sizeof(board));
  close(f);
}

//client commands
void client_understand(char * user_input) {
  if (strcmp("help", user_input) == 0) {
    print_help();
  } else if (strcmp("reset",user_input) == 0) {
    printf("RESET");
    reset_game();
  } else if (strcmp("clear",user_input) == 0) {
    printf("CLEAR\n");
    clear_screen();
  } else if (strcmp("exit",user_input) == 0) {
    printf("EXIT\n");
    exit_client();
  } else if (strcmp("print",user_input) == 0) {
    print_board();
  }
  else {
    printf("Type help if you're not sure what to do.\n");
  }
  
}

//first few words
void initiate_text() {
  printf("\nHello, welcome!\n");
  printf("Type in help if you're not sure what to do\n");
}

//prints help
void print_help() {
  int parent = fork();
  if (!parent) {
    execlp("cat","cat","help.txt",NULL);
  } else {
    wait(NULL);
  }
}

//clears the screen
void clear_screen() {
  int parent = fork();
  if (!parent) {
    execlp("clear","clear",NULL);
  } else {
    wait(NULL);
  }
}

//exits
void exit_client() {
  int parent = fork();
  if (!parent) {
    execlp("^C","^C",NULL);
  } else {
    wait(NULL);
  }
}

//prints the connect 4 board
void print_board() {
  int f = open("game.txt", O_RDONLY, 0666);
  char board [6][7];
  read(f,&board, sizeof(board));
  int r = 5;
  int c = 0;
  int i = 0;
  char line [15];
  printf("=============\n");
  for (;r > -1;r--) {
    line[14] = 0;
    i = 0;
    for (c = 0; c < 7; c++) {
      line[2 * i] = board[r][c];
      line[2 * i + 1] = ' ';
      i++;
    }
    printf("%s\n",line);
  }
  printf("=============\n");
  close(f);
}

//calculates the number of turns that have passed
int num_of_turns() {
  int f = open("game.txt", O_RDONLY, 0666);
  char board [6][7];
  read(f,&board, sizeof(board));
  int num = 0;
  int r = 0;
  int c = 0;

  for (; r < 6; r++) {
    for (c = 0; c < 7; c++) {
      if (board[r][c] != 'O') num++;
    }
  }
  close(f);
  return num + 1;
}

char * process_turn(char * user_input) {
  int f = open("game.txt", O_RDONLY, 0666);
  char board [6][7];
  read(f,&board, sizeof(board));
  close(f);
  int turns = num_of_turns();
  char piece [1];
  if (turns % 2 == 0) {
    piece[0] = 'X';
  } else {
    piece[0] = '#';
  }
  int val = atoi(user_input);
  if (val > 6) {
    return "Try again\n";
  } else if (val == 0) return "";
  int r = 0;
  for (;r < 6; r++) {
    if (board[r][val - 1] == 'O') {
      board[r][val - 1] = piece[0];
      break;
    }
  }
  f = open("game.txt",O_WRONLY, 0666);
  write(f, &board, sizeof(board));
  close(f);
  return "Success\n";
}

//checks if the user has won
int check_win(){
  int f = open("game.txt", O_RDONLY, 0666);
  char locations[6][7];
  read(f, &locations, sizeof(locations));
  int matches = 0;
  int r = 0;
  int c = 0;
  for (r = 0; r < 6; r++){
    for (c = 0; c < 4; c++){
      if (locations[r][c] != 'O'){
	if (locations[r][c] == locations[r][c+1]) matches++;
	if (locations[r][c] == locations[r][c+2]) matches++;
	if (locations[r][c] == locations[r][c+3]) matches++;
	if (matches == 3) return 1;
      }
      matches = 0;
    }
  }
  for (c = 0; c < 7; c++){
    for (r = 0; r < 3; r++){
      if (locations[r][c] != 'O'){
	if (locations[r][c] == locations[r+1][c]) matches++;
	if (locations[r][c] == locations[r+2][c]) matches++;
	if (locations[r][c] == locations[r+3][c]) matches++;
	if (matches == 3) return 1;
      }
      matches = 0;
    }
  }

  for (r = 0; r < 3; r++){
    for (c = 0; c < 4;c++){
      if (locations[r][c] != 'O'){
	if (locations[r][c] == locations[r+1][c+1]) matches++;
	if (locations[r][c] == locations[r+2][c+2]) matches++;
	if (locations[r][c] == locations[r+3][c+3]) matches++;
	if (matches == 3) return 1;
      }
      matches = 0;
    }
  }

  for (r = 3; r < 6; r++){
    for (c = 0; c < 4; c++){
      if (locations[r][c] != 'O'){
	if (locations[r][c] == locations[r-1][c+1]) matches++;
	if (locations[r][c] == locations[r-2][c+2]) matches++;
	if (locations[r][c] == locations[r-3][c+3]) matches++;
	if (matches == 3) return 1;
      }
      matches = 0;
    }
  }
  close(f);
  return -1;
}
