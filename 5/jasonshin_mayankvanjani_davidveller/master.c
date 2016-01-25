#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char ** map_maker(char * mapfile) {
  char ** maparray = (char **)malloc(sizeof(char *));
  //  char ** maparray;
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];
  read(fdMap, &mapStr, sizeof(mapStr));

  char * p = (char *)malloc(sizeof(char *) * 100);
  p = mapStr;
  //  printf("MAP:\n%s\n", mapStr);

  int i = 0;

  for (i = 0; p; i++) {
    char * mapLine = (char *)malloc(sizeof(char *));
    mapLine = strsep( &p, "\n" );
    //printf("%s",p);
    //sleep(1);
    maparray[i] = mapLine;
 
    // Next Line Prints the entire Map!!! ////////////
    //    printf("maparray[%d]:\t%s\n",i, maparray[i]);   

  }
  return maparray;
}

void print_map(char ** maparray) {
  //Print the Entire 2D Array                    
  int x, y = 0;
  for (x = 0; x < 12; x++) {
    for (y = 0; y < 12; y++) {
      printf("%c ", maparray[x][y]);
      //printf("maparray[%d][%d]:%c\n", x, y, maparray[x][y]);
    }
    printf("\n");
  }

  /*
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];  
  read(fdMap, &mapStr, sizeof(mapStr));
  printf("%s\n", mapStr);
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
    printf("\n\n");
    system("/bin/stty cooked");
    system("cat done.txt");
    //    printf("\nDONE WITH THE QUEST\n");
    exit(0);
    //    printf("%s", printer);
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
  char * clear = "\033[2J";

  char ** map = map_maker("map.txt");
  int coord[2] = {1, 1};

  printf("%s\n", clear);
  printf("%*s\n", 72, "Welcome, this is a Beta test of our new text based D&D game\n");
  printf("%*s\n", 70, "Created by Jason Shin, David Veller, and Mayank Vanjani\n");
  printf("%*s\n", 47, "Hope You Enjoy!!!\n");
  printf("%*s\n", 50, "**Press Enter to continue**");

  char s[100];
  fgets(s, sizeof(s), stdin);

  while (1) {
    char c;
    printf("%s\n", clear);
    printf("Use w,s,a,d to Move Around the Map and Space to Quit\n\n");
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
	printf("\tInvalid Move\n");
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
	printf("\tInvalid Move\n");
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
	printf("\tInvalid Move\n");
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
	printf("\tInvalid Move\n");
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
