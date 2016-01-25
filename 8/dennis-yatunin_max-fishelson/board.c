#include <stdio.h>
#include <stdlib.h>

typedef struct {int rows; int cols; int moves[20][20][2]; int shipnum; int ships[10];} board;

void newBoard(board *new){
  new->rows = 0;
  new->cols = 0;
  new->shipnum = 0;
  int i;
  for(i=0; i<10; i++){
    (new->ships)[i]=0;
  }

  char in[256];
  printf("To play on a standard board, type 's'.  To play on a custom board, where you choose board dimensions and number of ships, type 'c'.\n");
  scanf("%s",&in);
  while(in[0]!='s'&&in[0]!='c'){
    printf("Invalid input.  To play on a standard board, type 's'.  To play on a custom board, type 'c'.\n");
    scanf("%s",&in);
  }
  
  if(in[0]=='c'){
    printf("How many rows do you want the gameboard to have? Choose a number from 5 to 20.\n");
    scanf("%d",&(new->rows));
    while(new->rows < 5 || new->rows > 20){
      printf("Invalid input: Choose a number from 5 to 20.\n");
      scanf("%d",&(new->rows));
    }

    printf("How many columns do you want the gameboard to have? Choose a number from 5 to 20.\n");
    scanf("%d",&(new->cols));
    while(new->cols < 5 || new->cols > 20){
      printf("Invalid input: Choose a number from 5 to 20.\n");
      scanf("%d",&(new->cols));
    }

    printf("How many ships do you want the gameboard to have? Choose a number from 1 to 10.\n");
    scanf("%d",&(new->shipnum));
    while(new->shipnum < 1 || new->shipnum > 10){
      printf("Invalid input: Choose a number from 1 to 10.\n");
      scanf("%d",&(new->shipnum));
    }

    for(i=0; i<new->shipnum; i++){
      printf("How long do you want the ship #%d to be? Choose a number from 2 to 7.\n",i);
      scanf("%d",&((new->ships)[i]));
      while((new->ships)[i] < 2 || (new->ships)[i] > 7){
        printf("Invalid input: Choose a number from 2 to 7.\n");
        scanf("%d",&((new->ships)[i]));
      }
    }
  }else{
    new->rows = 10;
    new->cols = 10;
    new->shipnum = 5;
    new->ships[0] = 2;
    new->ships[1] = 3;
    new->ships[2] = 3;
    new->ships[3] = 4;
    new->ships[4] = 5;
  }
}

void copyBoard(board *new, board *old){
  new->rows = old->rows;
  new->cols = old->cols;
  new->shipnum = old->shipnum;
  int i;
  for(i=0; i<new->shipnum; i++){
    (new->ships)[i]=(old->ships)[i];
  }
}

void printMyBoard(board *b){
  char out[66]; //printing largest board
  out[0]=' ';
  out[1]=' ';
  out[2]=' ';
  int c = 3;
  int i;
  for(i=0; i<b->cols; i++){
    if(i<9){
      out[c]=i+49;
      out[c+1]=' ';
      out[c+2]=' ';
      c+=3;
    }else if(i<19){
      out[c]='1';
      out[c+1]=i+39;
      out[c+2]=' ';
      c+=3;
    }else{
      out[c]='2';
      out[c+1]=i+29;
      out[c+2]=' ';
      c+=3;
    }
  }
  out[c]='\n';
  out[c+1]='\n';
  out[c+2]=NULL;
  printf(out);
  
  for(i=10; i<b->cols+1; i++){
    out[3*i+1]=' ';
  }
  
  for(i=0; i<b->rows; i++){
    out[0]=i+65;
    int j;
    for(j=0; j<b->cols; j++){
      if(b->moves[i][j][0]+1){
        if(b->moves[i][j][1]){
          out[3*j+3]='X';
        }else{
          out[3*j+3]='O';
        }
      }else{
        if(b->moves[i][j][1]){
          out[3*j+3]='+';
        }else{
          out[3*j+3]='-';
        }
      }
    }
    printf(out);
  }
}

void printOtherBoard(board *b){
  char out[66]; //printing largest board
  out[0]=' ';
  out[1]=' ';
  out[2]=' ';
  int c = 3;
  int i;
  for(i=0; i<b->cols; i++){
    if(i<9){
      out[c]=i+49;
      out[c+1]=' ';
      out[c+2]=' ';
      c+=3;
    }else if(i<19){
      out[c]='1';
      out[c+1]=i+39;
      out[c+2]=' ';
      c+=3;
    }else{
      out[c]='2';
      out[c+1]=i+29;
      out[c+2]=' ';
      c+=3;
    }
  }
  out[c]='\n';
  out[c+1]='\n';
  out[c+2]=NULL;
  printf(out);
  
  for(i=10; i<b->cols+1; i++){
    out[3*i+1]=' ';
  }
  
  for(i=0; i<b->rows; i++){
    out[0]=i+65;
    int j;
    for(j=0; j<b->cols; j++){
      if(b->moves[i][j][0]+1){
        if(b->moves[i][j][1]){
          out[3*j+3]='X';
        }else{
          out[3*j+3]='-';
        }
      }else{
        if(b->moves[i][j][1]){
          out[3*j+3]='+';
        }else{
          out[3*j+3]='-';
        }
      }
    }
    printf(out);
  }
}

void parseGuess(char *s, int *coors){
  coors[0]=s[0]-65;
  coors[1]=atoi(s+1)-1;
}

void setBoard(board *new){
  int i;
  for(i=0; i<new->rows; i++){
    int j;
    for(j=0; j<new->cols; j++){
      new->moves[i][j][0]=-1;
      new->moves[i][j][1]=0;
    }
  }
  char in[4] = "\0\0\0";
  for(i=0; i<new->shipnum; i++){
    printMyBoard(new);
    printf("Place a ship of length %d.\n", new->ships[i]);
    printf("First, enter the coordinates of the upper-left most square of the ship, like 'A1' with the A capitalized.\n");
    scanf("%s",&in);
    int coors[2];
    parseGuess(in,coors);
    printf("Now, enter 'v' to place the ship vertically and 'h' to place the ship horizontally.\n");
    scanf("%s",&in);
    //add making sure boat stays on board and does not go over other boats
    if(in[0]=='v'){
      int j;
      for(j=0; j<new->ships[i]; j++){
        new->moves[coors[0]+j][coors[1]][0]=i;
      }
    }
    if(in[0]=='h'){
      int j;
      for(j=0; j<new->ships[i]; j++){
        new->moves[coors[0]][coors[1]+j][0]=i;
      }
    }
  }
}

void move(board *b){
  printf("Enter the coordinates of your guess, like 'A1' with the A capitalized.\n");
  char in[4]="\0\0\0";
  scanf("%s",&in);
  int coors[2];
  parseGuess(in,coors);
  //add making sure valid coors and guess never been guessed before
  if((b->moves)[coors[0]][coors[1]][0]+1){
    printf("Hit!\n");
    (b->moves)[coors[0]][coors[1]][1]=1;
    (b->ships)[(b->moves)[coors[0]][coors[1]][0]]--;
    if(!(b->ships)[(b->moves)[coors[0]][coors[1]][0]]){
      printf("You sunk ship #%d!\n",(b->moves)[coors[0]][coors[1]][0]);
    }
  }else{
    printf("Miss!\n");
    (b->moves)[coors[0]][coors[1]][1]=1;
  }
}

int gameOver(board *b){
  int i;
  for(i=0; i<b->shipnum; i++){
    if(b->ships[i]){
      return 0;
    }
  }
  return 1;
}

int main(){
  board b1;
  newBoard(&b1);
  board b2;
  copyBoard(&b2,&b1);
  setBoard(&b1);
  setBoard(&b2);
  while(!(gameOver(&b1)||gameOver(&b2))){
    printOtherBoard(&b2);
    move(&b2);
    printMyBoard(&b2);
    printOtherBoard(&b1);
    move(&b1);
    printMyBoard(&b1);
  }
}
    
