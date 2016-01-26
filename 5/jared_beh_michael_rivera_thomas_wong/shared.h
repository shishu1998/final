#ifndef SHARED_H
#define SHARED_H

typedef struct {
  char mini_board[3][3];  // Each board is 3x3 board!
  char winner;            // 0, X, O who won this board?
  char full;              // 0, 1 is this board full?
} board;

extern board super_board[3][3];
extern int socket_id, socket_client;
extern int socket_id_2, socket_client_2;
extern char line[100];
extern int prev[2] = {-1,-1};
#endif
