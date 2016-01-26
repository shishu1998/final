#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

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
          out[3*j+3]=b->moves[i][j][0]+48;
        }
      }else{
        if(b->moves[i][j][1]){
          out[3*j+3]='@';
        }else{
          out[3*j+3]='-';
        }
      }
    }
    printf(out);
  }
}

void printOtherBoard(board *b){
  char out[66]; //printing largest possible board
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
          out[3*j+3]='@';
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

int randomInt(int n) {
  int urandom_handle = open("/dev/urandom", O_RDONLY);
  int random;
  read(urandom_handle, &random, 4);
  close(urandom_handle);
  return abs(random%n);
}

void randSetBoard(board *new){ //NOTE: This is algorithm produces a truly random board setup, with all setups equally likely... not easy to do.
  int sort[new->shipnum];
  int i;
  int count = 0;
  for(i=7; i>1; i--){
    int j;
    for(j=0; j<new->shipnum; j++){
      if(new->ships[j]==i){
	sort[count]=j;
	count++;
      }
    }
  }
  
  int hor[new->rows][new->cols];
  int ver[new->rows][new->cols];
  
  for(i=0; i<new->rows; i++){
    int j;
    for(j=0; j<new->cols; j++){
      new->moves[i][j][0]=-1;
      new->moves[i][j][1]=0;
      hor[i][j]=(new->cols)-j;
      ver[i][j]=(new->rows)-i;
    }
  }
  for(i=0;i<new->shipnum;i++){
    int c=0;
    int j;
    for(j=0; j<new->rows; j++){
      int k;
      for(k=0; k<new->cols; k++){
        if(hor[j][k]>=(new->ships)[sort[i]]) c++;
        if(ver[j][k]>=(new->ships)[sort[i]]) c++;
      }
    }
    
    if(!c){
      printf("The CPU is taking a while to find a random setup.  Consider using a larger board or fewer ships.\n");
      randSetBoard(new);
      return;
    }
    
    int d = randomInt(c);
    int xcor;
    int ycor;
    int isHor;
    for(j=0; j<new->rows; j++){
      int k;
      for(k=0; k<new->cols; k++){
        if(hor[j][k]>=(new->ships)[sort[i]]){
          d--;
          if(!d){
            xcor = j;
            ycor = k;
            isHor = 1;
          }
        }
      }
    }
    
    for(j=0; j<new->rows; j++){
      int k;
      for(k=0; k<new->cols; k++){
        if(ver[j][k]>=(new->ships)[sort[i]]){
          d--;
          if(!d){
            xcor = j;
            ycor = k;
            isHor = 0;
          }
        }
      }
    }
    
    if(isHor){
      for(j=0; j<(new->ships)[sort[i]]; j++){
        new->moves[xcor][ycor+j][0]=sort[i];
        hor[xcor][ycor+j]=0;
        int k;
        for(k=xcor; k>=0 && ver[k][ycor+j]; k--){
          ver[k][ycor+j] = xcor-k;
        }
      }
      for(j=ycor-1; j>=0 && hor[xcor][j]; j--){
        hor[xcor][j] = ycor - j;
      }
    }else{
      for(j=0; j<(new->ships)[sort[i]]; j++){
        new->moves[xcor+j][ycor][0]=sort[i];
        ver[xcor+j][ycor]=0;
        int k;
        for(k=ycor; k>=0 && hor[xcor+j][k]; k--){
          hor[xcor+j][k] = ycor-k;
        }
      }
      for(j=xcor-1; j>=0 && ver[j][ycor]; j--){
        ver[j][ycor] = xcor - j;
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
