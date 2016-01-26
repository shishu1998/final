#include "utils.h"
#include <stdio.h>

void battleship() {
	printf(
		"Mega Battleship (c) 2016 Dionysus Yatunin & Maximus Fishelson. "
		"All rights reserved.\n\n\n"
		);
	char name[MAX_INPUT];
	printf("What is your name, player?\n");
	get_input(name, MAX_INPUT);
	int keep_playing = 1;
	char input[MAX_INPUT];
	int choice;
	while (keep_playing)
		printf(
			"Alright then, %s, would you like to start "
			"a new game or join an existing one?\n", name
			);
		choice = which(
			input, MAX_INPUT,
			"Please type \"start\" or \"join\".",
			"n", "new", "s", "start", "e", "existing", "j", "join", NULL
			);
		if (choice < 4) {
			start_game(input, name);
		}
		else {
			join_game(input, name);
		}
		printf(
			"Oh, no! You just lost the game. Do you want to play again?\n"
			);
		choice = which(
			input, MAX_INPUT,
			"Please type \"yes\" or \"no\".",
			"y", "yes", "yeah", "sure", "n", "no", "nope", "nah", NULL
			);
		if (choice < 4) {
			printf(NEW_SCREEN);
		}
		else {
			keep_playing = 0;
		}
	}
}

void start_game(char *input, char *name) {

}

void join_game(char *input, char *name) {

}
