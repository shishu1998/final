#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void map_maker(char * mapfile) {
  char ** maparray;
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];
  read(fdMap, &mapStr, sizeof(mapStr));
  char * p = mapStr;
  printf("map: %s", mapStr);
  while (mapStr) {
    char * mapLine = strsep( &p, "\n" );
    int i = 0;
    for (i = 0; i < sizeof(mapLine); i++) {
      printf("char %d: %c\n", i, mapLine[i]);
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
