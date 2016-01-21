typedef struct {

  char mini_board[3][3];  // Each board is 3x3 board!
  char winner;            // 0,X,O who won this board?
  char full;              // is this board full?

} board;

board super_board[3][3];

void start_game();            // initialize empty board
int turn( char R, char C, char r, char c);    // react to legal or illegal player input
char check_super_win();  // check to see if the super_board is won
char check_win( char[][] );   // check to see if a board is won
char* parse( board[][] );     // prepare String for client.
