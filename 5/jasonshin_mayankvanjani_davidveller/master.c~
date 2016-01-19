#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void printMap() {
  int fdMap = open("map.txt", O_RDONLY);
  char mapStr[10000];  
  read(fdMap, &mapStr, sizeof(mapStr));
  printf("%s\n", mapStr);
  return;
}

int main() {
  printMap();
  return 0;
}
