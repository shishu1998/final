#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void map_maker(char * mapfile) {
  char ** maparray = (char **)malloc(sizeof(char **) * 100);
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];
  read(fdMap, &mapStr, sizeof(mapStr));
  char * p = (char *)malloc(sizeof(char *) * 100);
  p = mapStr;
  printf("map:\n%s", mapStr);
  int y = 0;
  for (y = 0; p; y++) {
    char * mapLine = (char *)malloc(sizeof(char *) * 100);
    mapLine = strsep( &p, "\n" );
    printf("%s",p);
    //sleep(1);
    
    int x = 0;
    for (x = 0; x < strlen(mapLine); x++) {
      maparray[y][x] = mapLine[x];
      printf("char %d: %c\n", x, mapLine[x]);
    }
    
  }
  return;
}

void printMap() {
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];  
  read(fdMap, &mapStr, sizeof(mapStr));
  printf("%s\n", mapStr);
  return;
}

int main() {
  map_maker("map.txt");
  return 0;
}
