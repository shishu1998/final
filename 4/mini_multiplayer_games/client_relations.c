#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client_relations.h"

char * understand(char * user_input) {
  if (strcmp("help", user_input) == 0) {
    return print_help();
  }
  return NULL;
}
void initiate_text() {
  printf("Hello, welcome!\n");
  printf("Type in help if you're not sure what to do");
}

char * print_help() {
  return "To initiate a new game:\nType 1 for Connect 4\nType 2 for Tic-Tac-Toe\nType 3 for Connect the Dots\n";
}
