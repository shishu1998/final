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
  printf("MAP:\n%s\n", mapStr);

  int i = 0;

  for (i = 0; p; i++) {
    char * mapLine = (char *)malloc(sizeof(char *));
    mapLine = strsep( &p, "\n" );
    //printf("%s",p);
    //sleep(1);
    maparray[i] = mapLine;
 
    // Next Line Prints the entire Map!!! ////////////
    //    printf("maparray[%d]:\t%s\n",i, maparray[i]);   

    /*
    
      for (x = 0; x < strlen(mapLine); x++) {
      printf("Testing\n");
      maparray[y][x] = mapLine[x];
      printf("char %d: %c\n", x, mapLine[x]);
    }
    
    */
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

int main() {
  char ** map = map_maker("map.txt");
  int coord[2] = {1, 1}
  while (1) {
    char c;
    print_map(map);
    system("/bin/stty raw");
    c = getchar();
    int curX = coord[0];
    int curY = coord[1];
    if (c == 'w') {
      char testChar = map[curX - 1][curY];
      if (testChar != '-' || testChar != 'x') {
	
  return 0;
}
