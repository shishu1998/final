#ifndef BOARD_H
#define BOARD_H

typedef struct {
  int rows;
  int cols;
  int moves[20][20][2];
  int shipnum;
  int ships[10];
} board;

void newBoard(board *new);

void copyBoard(board *new, board *old);

void printMyBoard(board *b);

void printOtherBoard(board *b);

void parseGuess(char *s, int *coors);

void setBoard(board *new);

int randomInt(int n);

void randSetBoard(board *new);

void move(board *b);

int gameOver(board *b);

#endif
