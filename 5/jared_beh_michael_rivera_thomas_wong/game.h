typedef struct {

  char[3][3] mini_board;  // Each board is 3x3 board!
  char winner;            // 0,X,O who won this board?

} board;

board super_board[3][3];

void error_check( int );      // defensive programming!
void start_game();            // initialize empty board, random choose first player
void turn( board[][], char R, char C, char r, char c);    //react to player input
char check_super_win( board[][] );
char check_win( char[][] );   // check to see if a board is won
void end_game();              // restart or exit message, close connections, quit game.
char* parse( board[][] );     // prepare String for client.
