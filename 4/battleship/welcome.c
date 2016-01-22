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



  /*
  command ** user_commands;
        
  //initial user input
  printf("\nSlam$ ");
  char user_input[256];
  fgets(user_input, sizeof(user_input), stdin);  
  //erases the new line
  len_of_input = strlen(user_input);
  user_input[len_of_input-1] = 0; 
        
  //if the user did not type exit, it keeps going 
  while(strcmp(user_input, "exit")) {
    parseAndRun(user_input);
    printf("Slam$ ");
    memset(user_input,0,sizeof(user_input));
    //printf("USER INPUT = %s\n\n", user_input);
    //continues getting user input
    fgets(user_input, sizeof(user_input), stdin);
    len_of_input = strlen(user_input);
    user_input[len_of_input-1] = 0;
    
    */
    
