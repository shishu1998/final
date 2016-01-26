#include "utils.h"
#include "board.h"
#include "connections.h"
#include "game.h"
#include <stdio.h>

void battleship() {
	printf(
		"Mega Battleship (c) 2016 Dionysus Yatunin & Maximus Fishelson.\n"
		"All rights reserved.\n\n\n"
		);
	char name[MAX_INPUT];
	get_input(
		"What is your name, player?\n",
		name, MAX_INPUT
		);

	int keep_playing = 1;
	char input[MAX_INPUT];
	int temp;

	while (keep_playing) {
		printf("Alright then, %s, ", name);
		temp = select_input(
			"would you like to start a new game or join an existing one?\n",
			input, MAX_INPUT,
			"Please type \"start\" or \"join\".",
			"n", "new", "s", "start", "e", "existing", "j", "join", NULL
			);
		if (temp < 4) {
			start_game(input, name);
		}
		else {
			join_game(input, name);
		}

		temp = select_input(
			"Looks like the game is over. Do you want to play again?\n",
			input, MAX_INPUT,
			"Please type \"yes\" or \"no\".",
			"y", "yes", "yeah", "sure", "n", "no", "nope", "nah", NULL
			);
		if (temp > 3) {
			keep_playing = 0;
		}
	}
}

void print_waiting_message(board_list *bl, int id_num) {
	if (bl->num_boards == 2) {
		printf("Waiting for %s...\n", bl->boards[id_num].name);
	}
	else {
		printf("Waiting for other players...\n");
	}
}

void connect_to_opponents(
	int* socks_to_clients, int num_opponents, board_list *bl, char* name
	) {
	int temp;
	int listening_sock = server_listener();

	for (temp = 0; temp < num_opponents; temp++) {
		if (temp < num_opponents - 1) {
			printf("Waiting for remaining %d players...\n", num_opponents);
		}
		else if (num_opponents > 1) {
			printf("Waiting for last player...\n");
		}
		else {
			printf("Waiting for opponent...\n");
		}

		socks_to_clients[temp] = server_to_client(listening_sock);
		read(
			socks_to_clients[temp],
			bl->boards[temp + 1].name, MAX_INPUT
			);
		printf("%s has joined your game.\n", bl->boards[temp + 1].name);
		write(
			socks_to_clients[temp],
			name, MAX_INPUT
			);
	}

	close(listening_sock);
}

void game_loop_server(
	board_list *bl, int *socks_to_clients,
	int num_opponents, char *buf, int buf_size
	) {
	int temp, value;

	while (game_continues(bl)) {
		print_other_boards(0, bl);

		if (!gameOver(&bl->boards[0])) {
			if (num_opponents == 1) {
				move(&bl->boards[0]);
			}
			else {
				move_multiplayer(0, bl, buf, buf_size);
			}
		}
		
		print_waiting_message(bl, 1);

		for (temp = 0; temp < num_opponents; temp++) {
			read(
				socks_to_clients[temp],
				buf, buf_size
				);
			value = (int)strtol(buf, (char **)NULL, 10);
			move_auto(bl, value);
		}
		for (temp = 0; temp < num_opponents; temp++) {
			write(
				socks_to_clients[temp],
				bl, sizeof(board_list)
				);
		}

		printf("Your board:\n");
		printMyBoard(&bl->boards[0]);
	}
}

void start_game(char *input, char *name) {
	int temp, num_opponents, socks_to_clients[11];
	board_list bl;

	temp = select_input(
		"How many people will be allowed to join your game?\n",
		input, MAX_INPUT,
		"Please type a number from 1 to 10.",
		"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", NULL
		);
	num_opponents = temp + 1;
	new_board_list(&bl, num_opponents + 1, name);
	connect_to_opponents(socks_to_clients, num_opponents, &bl, name);

	for (temp = 0; temp < num_opponents; temp++) {
		sprintf(input, "%d", temp + 1);
		write(socks_to_clients[temp], input, MAX_INPUT);
		read(socks_to_clients[temp], input, MAX_INPUT);
		write(socks_to_clients[temp], &bl, sizeof(board_list));
	}

	printf("Your %d-person game now begins.\n", bl.num_boards);
	setBoard(&bl.boards[0]);

	printf("Your board:\n");
	printMyBoard(&bl.boards[0]);

	print_waiting_message(&bl, 1);
	for (temp = 0; temp < num_opponents; temp++) {
		read(socks_to_clients[temp], &bl.boards[temp + 1], sizeof(board));
	}
	for (temp = 0; temp < num_opponents; temp++) {
		write(socks_to_clients[temp], &bl, sizeof(board_list));
	}

	game_loop_server(&bl, socks_to_clients, num_opponents, input, MAX_INPUT);
}

int connect_to_host(int is_ip, char *input) {
	int sock_to_server;

	while (1) {
		if (is_ip) {
			get_input(
				"What is the IP address of the machine "
				"on which the game is being hosted?\n",
				input, MAX_INPUT
				);
			sock_to_server = client_to_server_addr(input);
			if (sock_to_server != -1) {
				break;
			}
		}

		else {
			get_input(
				"What is the hostname of the machine "
				"on which the game is being hosted?\n",
				input, MAX_INPUT
				);
			sock_to_server = client_to_server_name(input);
			if (sock_to_server != -1) {
				break;
			}
		}

		printf(
			"Uh-oh! It appears that your machine was unable to "
			"connect to %s. Please make sure that you are connected "
			"to the internet and that %s denotes a machine currently "
			"hosting a game of Mega Battleship (c).\n", input, input
			);
	}

	return sock_to_server;
}

void print_starting_text(char *input, board_list *bl, int my_id) {
	printf("%s's %d-person game now begins.\n", input, bl->num_boards);

	if (bl->num_boards > 2) {
		printf("Your opponents are:\n");

		int temp;
		for (temp = 0; temp < bl->num_boards; temp++) {
			if (temp == my_id) {
				continue;
			}
			printf("%s\n", bl->boards[temp].name);
		}
	}
}

void game_loop_client(
	board_list *bl, int sock_to_server,
	int id_num, char *buf, int buf_size
	) {
	int temp, value;

	while (game_continues(bl)) {
		print_other_boards(id_num, bl);

		if (!gameOver(&bl->boards[id_num])) {
			if (bl->num_boards == 2) {
				value = move(&bl->boards[0]);
			}
			else {
				value = move_multiplayer(id_num, bl, buf, buf_size);
			}
		}

		sprintf(buf, "%d", value);
		write(sock_to_server, buf, buf_size);

		print_waiting_message(bl, 0);

		read(sock_to_server, bl, sizeof(board_list));

		printf("Your board:\n");
		printMyBoard(&bl->boards[id_num]);
	}
}

void join_game(char *input, char *name) {
	int temp, sock_to_server, my_id;
	board_list bl;

	temp = select_input(
		"Do you want to access the game by IP address or hostname?\n",
		input, MAX_INPUT,
		"Please type \"ip\" or \"hostname\".",
		"ip", "address", "ip address", "hostname", "host", "name", NULL
		);
	sock_to_server = connect_to_host(temp < 3, input);

	write(sock_to_server, name, MAX_INPUT);
	read(sock_to_server, input, MAX_INPUT);
	printf("You have joined %s's game. Waiting for host computer...\n", input);

	read(sock_to_server, &bl, MAX_INPUT);
	my_id = (int)strtol(&bl, (char **)NULL, 10);
	write(sock_to_server, "ID Received", MAX_INPUT);
	read(sock_to_server, &bl, sizeof(board_list));
	print_starting_text(input, &bl, my_id);
	setBoard(&bl.boards[my_id]);

	printf("Your board:\n");
	printMyBoard(&bl.boards[my_id]);

	write(sock_to_server, &bl.boards[my_id], sizeof(board));
	print_waiting_message(&bl, 0);
	read(sock_to_server, &bl, sizeof(board_list));

	game_loop_client(&bl, sock_to_server, my_id, input, MAX_INPUT);
}
