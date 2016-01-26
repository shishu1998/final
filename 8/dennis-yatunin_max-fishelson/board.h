#ifndef BOARD_H
#define BOARD_H

typedef struct board{
	char name[MAX_INPUT];
	int rows;
	int cols;
	int moves[20][20][2];
	int shipnum;
	int ships[10];
} board;

typedef struct board_list {
	int num_boards;
	board boards[11];
} board_list;

void new_board_list(board_list *bl, int num, char* first_name);

int game_continues(board_list *bl);

void print_other_boards(int my_id, board_list *bl);

int move_multiplayer(int my_id, board_list *bl, char *buf, int buf_size);

void newBoard(board *new);

void copyBoard(board *new, board *old);

void printMyBoard(board *b);

void printOtherBoard(board *b);

void parseGuess(char *s, int *coors);

void setBoard(board *new);

int randomInt(int n);

void randSetBoard(board *new);

int move(board *b);

int gameOver(board *b);

#endif
