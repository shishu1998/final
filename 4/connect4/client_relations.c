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

void client_understand(char * user_input) {
  if (strcmp("help", user_input) == 0) {
    print_help();
  } else if (strcmp("clear",user_input) == 0) {
    printf("CLEAR\n");
    clear_screen();
  } else if (strcmp("exit",user_input) == 0) {
    printf("EXIT\n");
    exit_client();
  }
  else {
    printf("Type help if you're not sure what to do.\n");
  }
  
}

char * server_understand(char * user_input) {
  printf("WHAT\n");
  return "";

}
void initiate_text() {
  printf("\nHello, welcome!\n");
  printf("Type in help if you're not sure what to do\n");
}


void print_help() {
  int parent = fork();
  if (!parent) {
    execlp("cat","cat","help.txt",NULL);
  } else {
    wait(NULL);
  }
}

void clear_screen() {
  int parent = fork();
  if (!parent) {
    execlp("clear","clear",NULL);
  } else {
    wait(NULL);
  }
}

void exit_client() {
  int parent = fork();
  if (!parent) {
    execlp("^C","^C",NULL);
  } else {
    wait(NULL);
  }
}

/*void check_pid() {
  FILE * f = fopen("game.txt",
  }*/

/*

int main () {
  
  printf("%s", understand("help"));
  return 0;
}

int check_turn(int pid) {
  
}
*/
