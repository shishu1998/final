#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
  printf("Welcome to 'KEEP TALKING and NOBODY EXPLODES' in C, by Angela Chan and Dillon Zhang\n");
  printf("Please select 'manual' (m) or 'bomb' (b) to start.\n");
  printf("\tSelection: ");

  int fail = 1;
  while (fail) {
    char user_input[64];
    fgets(user_input, sizeof(user_input), stdin);
    *strchr(user_input, '\n') = 0;
    
    if (!strcmp(user_input,"manual") || !strcmp(user_input,"m")) {
      //exec manual
      fail = 0;
      printf("manual\n");
    } else if (!strcmp(user_input,"bomb") || !strcmp(user_input,"b")) {
      //exec bomb
      fail = 0;
      printf("bomb\n");
    } else {
      printf("Please enter 'manual' (m) or 'bomb' (b): ");
    }
  }

  return 0;
}
