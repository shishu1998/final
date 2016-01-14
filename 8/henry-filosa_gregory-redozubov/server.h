#ifndef server
#define server
#include <sys/stat.h>

void setup(){
  
  /*======== void setup() ==========
  Inputs: none
  Returns: nothing
  Creates file to hold usernames & passwords (userlist),
   file for usernames that are logged in(logged) and main directory
  ====================*/

  
  if (stat("/root", &st) == -1) {
    mkdir("/root", 0700);
  }   

  
  /*  char *directory = "root";

  struct stat dir = {0};
  if(stat(directory, &dir) == -1) {
      mkdir(directory, 0755);
      printf("created directory testdir successfully! \n");
    }

  int filedescriptor = open(directory/"log.txt", O_RDWR | O_APPEND | O_CREAT);
  if (filedescriptor < 0) {
      perror("Error creating my_log file\n");
      exit(-1);
    }
  */
}



void startup();
/*======== void startup() ==========
  Inputs: none
  Returns: nothing
  Creates semaphore to guard access to the userlist and and logged
  ====================*/

int authenticate();
/*======== int authenticate() ==========
  Inputs: char name[],char password[]
  Returns: boolean
  Checks userlist for username and password
  Checks logged to see if user already logged in
  Returns 0 if correct combination not present or the user is already logged in
  ====================*/

int add_user();
/*======== int add_user() ==========
  Inputs: char name[],char password[]
  Returns: boolean
  Checks userlist to see if name is already taken
  Return 1 if name is available and appends name & password to userlist, 
   creates directory folders(mailboxes) for the new user.
  Returns 0 of name is taken
  ====================*/

#endif
