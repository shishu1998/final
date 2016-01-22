#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char usrname[50];
  printf("=======WELCOME TO MARY'S PROM DATE SERVER=======\nYou want to take Mary out to PROM because she is an awesome person and if you don't want to then you have bad taste in women.");
  printf("Please create a username:\n");
  fgets(usrname, sizeof(usrname), stdin);
  printf("usrname: %s\n", usrname);

}
