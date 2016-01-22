#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

int main(){
    
    int i,n,len_of_input;
    time_t t;

    srand((unsigned) time(&t));
    n = rand() % 3;
  
   printf("WELCOME PLAYER\n");
   sleep(1);
   printf("ENTER YOUR NAME\n");
   
    char user_input[256];
    fgets(user_input, sizeof(user_input), stdin);
    len_of_input = strlen(user_input);
    user_input[len_of_input-1] = 0;
    
    printf("SO YOUR NAME IS: %s ", user_input);
    if (n == 1){
      printf("\nThat's nice...\n");
    }
    else printf ("\nNice!\n");
}

    
