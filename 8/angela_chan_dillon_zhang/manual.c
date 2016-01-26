#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "color.c"

int main() {
  textcolor(RESET, WHITE, BLACK); //Reseting the Color
  printf("\e[1;1H\e[2J\n"); //Clears the Screen
  
  textcolor(BRIGHT, BLUE, WHITE);
  printf("This is the Manual component of Attempting Diffusal.\n\n");
  textcolor(RESET, WHITE, BLACK);

  int age = fork();
  int information;
  int waiting;
  
  if (age) {
    waiting = wait(&information);
    printf("\nEnter 'next' to continue: ");
  } else {
    execlp("cat", "cat", "asciiart/manual/mancover.dat", NULL);
  }

  int pagecounter = -1;

  while(1) {
    char user_input[64];
    int new_page = 0;
    
    fgets(user_input, sizeof(user_input), stdin);
    *strchr(user_input, '\n') = 0;

    if (!strcmp(user_input,"exit")) {
      textcolor(BRIGHT, RED, BLACK);
      printf("Goodbye! Thanks for playing!");
      textcolor(RESET, WHITE, BLACK);
      exit(0);
    } else if (!strcmp(user_input,"next")) {
      if (pagecounter < 100 /*Length of Manual*/) {
	pagecounter++;
	new_page = 1;
      } else {
	textcolor(BRIGHT, RED, BLACK);
	printf("Sorry you have reached the end of the manual.");
	textcolor(RESET, WHITE, BLACK);
      }
    } else if (!strcmp(user_input,"back")) {
      if (pagecounter > 0) {
	pagecounter--;
	new_page = 1;
      } else {
	textcolor(BRIGHT, RED, BLACK);
	printf("Sorry you have reached the beginning of the manual.");
	textcolor(RESET, WHITE, BLACK);
      }
    } else {
      textcolor(BRIGHT, RED, BLACK);
      printf("Sorry, %s is not a valid command.", user_input);
      textcolor(RESET, WHITE, BLACK);
    }

    if (new_page) {
      new_page = 0;
      printf("\e[1;1H\e[2J\n");
      char *filename;
      sprintf(filename, "asciiart/manual/%d%d.dat", pagecounter / 10, pagecounter % 10);
      age = fork();
      if (age) {
	waiting = wait(&information);
      } else {
	execlp("cat", "cat", filename, NULL);
      }
    }

    printf("\nPlease enter 'next', 'back', or 'exit': ");
  }
  return 0;
}
