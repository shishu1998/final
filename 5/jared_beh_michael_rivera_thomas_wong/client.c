#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include "game.c"

int main(){
  char* clear = "\x1b[2J";
  char* hide =  "\x1b[?25l";
  char* show =  "\x1b[?25h";
  char* go = "\x1b[0;0H";
  int socket_id;
  //server to client board stuff
  char buffer[84];
  //client input stuff
  char buffer2[256];
  //client to server stuff
  char buffer3[5];
  int i;
  int addrs;
  char *server_ip;
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(24600);
  inet_aton(server_ip,&(sock.sin_addr));
  bind(socket_id,(struct sockaddr*)&sock,sizeof(sock));
  i=connect(socket_id,(struct sockaddr*)&sock,sizeof(sock));
  printf("Connected to socket:%d",i);
<<<<<<< HEAD
  printf("""%s %s %sWelcome to Ultimate Tic-Tac-Toe, the better way to play\nHave you ever felt bored with Tic-Tac-Toe? Do you think the game is too simple?\nHave you realized that the second player can never win?\n\nWell fear not, we made the game more complicated!\nUltimate Tic-Tac-Toe has the same premise as the original game, to get three in a row.\nHowever, you'll be playing on a 3x3 of 3x3's. To win, one must get three in a row of the\nlarger 3x3 boards, which can only be claimed by getting three squares in a row on that board.\nThere is one more catch though. The game starts with one player making a mark in any\nsquare on any of the nine boards. Then their opponent must make a mark in the board which\ncorresponds to the square of the first mark. If a mark is made in the upper lefthand\ncorner of a board, then the subsequent mark must be made on the upper lefthand board.\n\nHAVE FUN!!!\n(Press any key to continue)\n""",hide,clear,go);
fgets( buffer2, sizeof(buffer2), stdin );
  
// while(1){
    //Reads in who starts the game
   /*
  printf("Explanation of GAME HERE




  ");*/
  while(1){
    read(socket_id,buffer,sizeof(buffer));
    if(buffer[0]=='6'){
      close(socket_id);
      printf("Server down lower than Atlantis\n");
      exit(0);
    }
    if(buffer[0] == '3' || buffer[0] == '4'){
      break;
    }
    int i = 3;
    int c = 0;
    int q = 0;
    char outpu[612];
    //outpu is the board display of 35x17
    //to account for \n 36*17= 612
    //rows are larger due to the following format
    // 4 | 6 | 7 =  0
    //-----------=  1
    // 5 | 9 | 0 =  2   <- upper left corner design
    //-----------=  3
    // 1 | 3 | 8 =  4
    //============  5
    //123456789012
    //    while(q < 17){
      //checks if odd or even row
    while(q < 17){
      if((q % 2) == 1){
	if(((c + 1) % 4) == 0){
	  if(((c + 1) % 12) == 0){
	    outpu[c] = '=';
	  }else{
	    outpu[c] = '+';
	  }
	}else{
	  outpu[c] = '-';
	}
      }else{
	if((c % 2) == 0){
	  outpu[c] = ' ';
	}else{
	  if(((c + 1) % 12) == 0){
	    outpu[c] = '=';
	  }else if(((c + 1) % 4) == 0){
	    outpu[c] = '|';
	  }else{
	    outpu[c] = buffer[i];
	    i++;
	  }
	}
      }
      c++;
      if(c == 35){
	q++;
	outpu[c] = '\n';
	c++;
      }
    }
    //Prints board
    printf("%s %s %s%s",hide,clear,go,buffer);
    //Ask miniboard
    char BdR;
    char BdC;
    char SqR;
    char SqC;
    //Because we're passing a string -1 would take 2 characters so use 5 instead
    if(buffer[1] == '5'){
      while(1){
      	printf("\nYou may choose which of the larger boards to play on.\nPlease select the row(0,1,2) and column(0,1,2) of the larger board(r,c)\nwhere (0,0) is the top left\n");
	fgets( buffer2, sizeof(buffer2), stdin );
	if((buffer2[0] == '0' || buffer2[0] == '1' || buffer2[0] == '2') &&
	   (buffer2[2] == '0' || buffer2[2] == '1' || buffer2[2] == '2')){
	  BdR=buffer2[0];
	  BdC=buffer2[2];
	  break;
	}
	c = 0;
      }
    }else{
      BdR=buffer[1];
      BdC=buffer[2];
    }
    //Ask for square
    char *Rinpu;
    char *Cinpu;
    if(BdR == '0'){
      Rinpu = "top";
    }else if(BdR == '1'){
      Rinpu = "middle";
    }else{
      Rinpu = "bottom";
    }
    if(BdC == '0'){
      Cinpu = "left";
    }else if(BdC == '1'){
      Cinpu = "center";
    }else{
      Cinpu = "right";
    }
    while(1){
      printf("\nYou must choose which of the squares to play on in the %s %s board.\nPlease select the row(0,1,2) and column(0,1,2) of the smaller board(r,c)\nwhere (0,0) is the top left corner\n",Rinpu,Cinpu);
      fgets( buffer2, sizeof(buffer2), stdin );
	if((buffer2[0] == '0' || buffer2[0] == '1' || buffer2[0] == '2') &&
	   (buffer2[2] == '0' || buffer2[2] == '1' || buffer2[2] == '2')){
	  SqR=buffer2[0];
	  SqC=buffer2[2];
	  break;
	}
    }
    //Not really is we discussed format for client to server response
    //I think we agreed, although not positive, that server was the only
    //entity which would change the board
    printf("\nYour move is being processed");
    buffer3[0] = buffer[0];
    buffer3[1] = BdR;
    buffer3[2] = BdC;
    buffer3[3] = SqR;
    buffer3[4] = SqC;
    write(socket_id,buffer3,sizeof(buffer3));
 }
  
  //printf("%s %s %s%s",hide,clear,go,buffer);
  }

  /*
  printf("%s",clear);
  printf("%s",hide);
  printf("%s",show);
  printf("%s",go);
  */
  //hide,clear,go,stuff,\n,show
  return 0;
}
