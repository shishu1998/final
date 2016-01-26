#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "color.c"
#include "bomb_helper.h"

int main() {
  printf("\e[1;1H\e[2J\n");
  textcolor(BRIGHT, RED, BLACK);
  printf("This is the Bomb component of Attempting Diffusal.\n");
  textcolor(RESET, WHITE, BLACK);

  char user_input[64];

  int mod_number = 0;
  int game_over = 0;
  
  /* CREATE a module array */
  char filer[128];
  sprintf(filer, "asciiart/wires/w%d.dat", create_random() % 3 + 1);
  //printf("%s\n",filer);
  module *a = create_module(filer);
  
  module *b = create_module("asciiart/memory/m1.dat");

  sprintf(filer, "asciiart/symbols/s%d.dat", create_random() % 5 + 1);
  //printf("%s\n",filer);
  module *c = create_module(filer);

  sprintf(filer, "asciiart/keypad/k%d.dat", create_random() % 2 + 1);
  //printf("%s\n",filer);
  module *d = create_module(filer);

  sprintf(filer, "asciiart/button/b%d.dat", create_random() % 5 + 1);
  //printf("%s\n",filer);
  module *e = create_module(filer);
   
  module *modules[5] = {a, b, c, d, e};
  
  while (!completed_game(modules) && !game_over) { //!game_complete(module array) 
    //Show original Bomb
    draw_bomb();
    printf("Please select a module (1 - 5): ");
    fgets(user_input, sizeof(user_input), stdin);
    *strchr(user_input, '\n') = 0;

    mod_number = verify_input(user_input, modules);
    if (mod_number == -2) {
      game_over = 1;
    }
    while (mod_number >= 0){

      print_module(modules[mod_number]);
      
      printf("What do you do? ('%s' or 'back'): ", modules[mod_number]->visual_representation[1]);
      fgets(user_input, sizeof(user_input), stdin);
      *strchr(user_input, '\n') = 0;

      if (!strcmp("back", user_input)) {
	mod_number = -1;
      } else if (verify_module(modules[mod_number], user_input)) {
	printf("\e[1;1H\e[2J\n");
	printf("\tThat was correct!\n");
	if (completed_module(modules[mod_number])) {
	  mod_number = -1;
	  printf("You successfully disarmed a module.\n");
	}
      } else {
	mod_number = -1;
	game_over = 1;
      }
    }
  }
  //Post Game (Either game_over is true or completed_game(modules) is true
  int age, information, waiting;
  if (game_over) {
    printf("\e[1;1H\e[2J\n");
    age = fork();
    if (age) {
      waiting = wait(&information);
      textcolor(RESET, WHITE, BLACK);
      printf("Sorry, You Lost! We hope you enjoyed and are willing to try again.");
    } else {
      textcolor(BRIGHT, RED, BLACK);
      execlp("cat", "cat", "asciiart/gameover.dat", NULL);
    }
  } else {
    printf("\e[1;1H\e[2J\n");
    age = fork();
    if (age) {
      waiting = wait(&information);
      printf("Congratz! You survived and disarmed the bomb.\n");
    } else {
      execlp("cat", "cat", "asciiart/victory.dat", NULL);
    }
  }
  return 0;
}
