#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "color.c"

int main() {
  textcolor(RESET, WHITE, BLACK); //Resets the color before the program starts
  textcolor(BRIGHT, RED, BLACK);
  printf("Welcome to Attempting Defusal, 'KEEP TALKING and NOBODY EXPLODES' in C, by Angela Chan and Dillon Zhang\n");
  textcolor(RESET, WHITE, BLACK);
  
  printf("Please select 'manual' (m) or 'bomb' (b) to start.\n");
  printf("\tSelection: ");

  int fail = 1;
  int errno, errorstatus;
  
  while (fail) {
    char user_input[64];
    fgets(user_input, sizeof(user_input), stdin);
    *strchr(user_input, '\n') = 0;
    
    if (!strcmp(user_input,"manual") || !strcmp(user_input,"m")) {
      //exec manual
      fail = 0;
      errorstatus = execl("./manual.out","./manual.out",NULL);

    } else if (!strcmp(user_input,"bomb") || !strcmp(user_input,"b")) {
      //exec bomb
      fail = 0;
      errorstatus = execl("./bomb.out","./bomb.out",NULL);

    } else if (!strcmp(user_input,"exit")) {
      //exiting
      printf("Goodbye!\n");
      exit(0);

    } else {
      //bad selection
      printf("Please enter 'manual' (m) or 'bomb' (b): ");
    }
    
    if (errorstatus == -1){
	printf("ERROR: %s\n",strerror(errno));
    }
  }

  return 0;
}
