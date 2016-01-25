#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "client_relations.h"

char * understand(char * user_input) {
  printf("WHAT\n");
  char * compareme = "help";
  if (strcmp(compareme, user_input) == 0) {
    printf("WHAT\n");
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

int main () {
  
  printf("%s", understand("help"));
  return 0;
}
