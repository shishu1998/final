#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char ** map_maker(char * mapfile) {
  char ** maparray = (char **)malloc(sizeof(char *));
  //  char ** maparray;
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];
  read(fdMap, &mapStr, sizeof(mapStr));

  char * p = (char *)malloc(sizeof(char *) * 100);
  p = mapStr;
  //  write( socket_client, "MAP:\n%s\n", mapStr);

  int i = 0;

  for (i = 0; p; i++) {
    char * mapLine = (char *)malloc(sizeof(char *));
    mapLine = strsep( &p, "\n" );
    //write( socket_client, "%s",p);
    //sleep(1);
    maparray[i] = mapLine;
 
    // Next Line Prints the entire Map!!! ////////////
    //    write( socket_client, "maparray[%d]:\t%s\n",i, maparray[i]);   

  }
  return maparray;
}

void print_map(char ** maparray) {
  //Print the Entire 2D Array                    
  int x, y = 0;
  for (x = 0; x < 12; x++) {
    for (y = 0; y < 12; y++) {
      write( socket_client, maparray[x][y], sizeof(maparray[x][y]));
      //write( socket_client, "maparray[%d][%d]:%c\n", x, y, maparray[x][y]);
    }
    write( socket_client, "\n", sizeof("\n"));
  }

  /*
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];  
  read(fdMap, &mapStr, sizeof(mapStr));
  write( socket_client, "%s\n", mapStr);
  */

  return;
}

void check_win (char ** map, int x, int y) {
  /*
  int z = open( "done.txt", O_RDONLY);
  char printer[10000];
  read( z, &printer, sizeof(printer));
  */
  if (map[x][y] == '$') {
    write( socket_client, "\n\n", sizeof("\n\n"));
    system("/bin/stty cooked");
    system("cat done.txt");
    //    write( socket_client, "\nDONE WITH THE QUEST\n");
    exit(0);
    //    write( socket_client, "%s", printer);
      /*
"\n
|---   |-----| |\    / |-----  |  \n
|   \  |     | | \   / |       |  \n
|    | |     | |  \  / |-----  |  \n
|   /  |     | |   \ / |       |  \n
|---   |-----| |    \/ |-----  .  \n ";
      */

    //    exit(0);
  }
}

int main() {
  int socket_id, socket_client;

  //create the socket                                                                
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  //bind to port/address                                                             
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4                                 
  listener.sin_port = htons(24601); //port #                                         
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address              
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));

  listen( socket_id, 1 );
  write( socket_client, "<server> listening\n", 100);

  socket_client = accept( socket_id, NULL, NULL );
  //write( socket_client, "<server> connected: %d\n", socket_client );
  //write( socket_client,  socket_client, "hello", 6 );

  char * clear = "\033[2J";

  char ** map = map_maker("map.txt");
  int coord[2] = {1, 1};

  write( socket_client, clear, sizeof(clear));
  write( socket_client, "\nWelcome, this is a Beta test of our new text based D&D game\n", 200);
  write( socket_client, "Created by Jason Shin, David Veller, and Mayank Vanjani\n", 200);
  write( socket_client, "Hope You Enjoy!!!\n", 200);
  write( socket_client, "**Press Enter to continue**", 200);

  char s[100];
  fgets(s, sizeof(s), stdin);

  while (1) {
    char c;
    write( socket_client, clear, sizeof(clear));
    write( socket_client, "Use w,s,a,d to Move Around the Map and Space to Quit\n\n", 200);
    print_map(map);

    int curX = coord[0];
    int curY = coord[1];
    system("/bin/stty raw");
    c = getchar();

    if (c == 'w') {
      char testChar = map[curX - 1][curY];
      if (testChar != '-' && testChar != 'x') {
	coord[0] = coord[0] - 1;
	check_win( map, coord[0], coord[1] );
	map[curX][curY] = ' ';
	map[curX - 1][curY] = '@';
      }
      else {
	//write( socket_client, "\tInvalid Move\n", 50);
	sleep(1);
      }
    }
    else if (c == 's') {
      char testChar = map[curX + 1][curY];
      if (testChar != '-' && testChar != 'x') {
        coord[0] = coord[0] + 1;
	check_win( map, coord[0], coord[1] );
        map[curX][curY] = ' ';
        map[curX + 1][curY] = '@';
      }
      else {
	//write( socket_client, "\tInvalid Move\n");
	sleep(1);
      } 
    }
    else if (c == 'a') {
      char testChar = map[curX][curY - 1];
      if (testChar != '|' && testChar != 'x') {
        coord[1] = coord[1] - 1;
	check_win( map, coord[0], coord[1] );
        map[curX][curY] = ' ';
        map[curX][curY - 1] = '@';
      }
      else {
	//write( socket_client, "\tInvalid Move\n");
	sleep(1);
      } 
    }
    else if (c == 'd') {
      char testChar = map[curX][curY + 1];
      if (testChar != '|' && testChar != 'x') {
        coord[1] = coord[1] + 1;
	check_win( map, coord[0], coord[1] );
        map[curX][curY] = ' ';
        map[curX][curY + 1] = '@';
      }
      else {
	//write( socket_client, "\tInvalid Move\n");
	sleep(1);
      } 
    }

    system("/bin/stty cooked");

    if (c == ' ') {
      exit(0);
    }

  }
  return 0;
}
