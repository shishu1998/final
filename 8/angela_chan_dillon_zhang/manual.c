#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "color.c"

int main() {
  textcolor(BRIGHT, BLUE, WHITE);
  printf("This is the Manual component.\n");
  textcolor(RESET, WHITE, BLACK);
  
  return 0;
}
