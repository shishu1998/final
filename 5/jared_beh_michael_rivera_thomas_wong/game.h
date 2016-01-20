typedef struct {

  char[3][3] mini_board;  // Each board is 3x3 board!
  char winner;       // NULL,X,O who won this board?

} board;

board super_board[3][3];


void error_check();    // defensive programming!
void start_game();     // initialize empty board, random choose first player
void turn( char, char, char, char );    //react to player input

void end_game();       // exit message, close connections, quit game.
