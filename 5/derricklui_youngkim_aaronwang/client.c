#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_LINE 256
#define MAX_NAME_LENGTH 32

/* 
 * 0: Merlin
 * 1: Percival
 * 2: Guy
 * 3: Morgana
 * 4: Assassin
 */

void storename(char name[]) {
  printf("Enter your name.\n");
  fgets(name, MAX_NAME_LENGTH, stdin);
  name = strtok(name, "\n");
  printf("Welcome, %s.\n", name);
}

void parse_input() {
  printf("inputinput\n");
  char input[MAX_LINE];
  fgets(input, MAX_LINE, stdin);
  if(input[0] == '/') {
    printf("input: %s", input);
    printf("no seg fault pls\n");
  }
}

int main() {
  char name[MAX_NAME_LENGTH];

  storename(name);

  while(1) {
    parse_input();
  }

  return 0;
}
