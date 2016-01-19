#include "lib.h"

int main() {

  // Make mail directory
  // Needs to be rwx* so that we can cd into it
  mkdir("mail", 0744);

  printf("mkdir\n");
  
  // Initialize user list flat file
  int userfile = creat("mail/users.csv", 0644);
  printf("touch\n");

  char line[] = "username,password\n";
  
  write(userfile, line, sizeof(line) - 1);
  printf("cat\n");

  // Will be zero if no errors occur
  return errno;
}
