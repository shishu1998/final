#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void make_profile(char *username) {

}

void find_username(char *username) {



}

int main() {
  char *usrname;
  char *newline;
  newline = (char *)malloc(sizeof(char *));
  usrname = (char *)calloc(50, sizeof(char*));
  newline = "\n";
  printf("=======WELCOME TO MARY'S PROM DATE SERVER=======\nYou want to take Mary out to PROM because she is an awesome person and if you don't want to \
then you have bad taste in women.\n");
  printf("Please create a username:\n");
  fgets(usrname, 1024, stdin);
  printf("username without new line: %s\n", usrname);
  strcat(usrname, newline);
  printf("username: %s\n", usrname);

  FILE* fd1 = fopen("username.txt", "a+");

  int fd2 = fwrite(usrname, 1, sizeof(usrname), fd1);
  if (fd2 == -1)
    printf("fd2 is broken: %s\n", strerror(errno));


  char *buffer = (char *)malloc(100*sizeof(char));
  fread(buffer, 1, 100, fd1);
  //int readfile = scanf(fd1, buffer, sizeof(buffer));
  printf("buffer: %s\n", buffer);

  fclose(fd1);
  return 0;
}
/*
  int fd1 = open("username.txt", O_RDONLY | O_WRONLY | O_APPEND);
  if (fd1 == -1)
    printf("fd1 is broken: %s\n", strerror(errno));
  
  int fd2 = write(fd1, usrname, sizeof(usrname));
  if (fd2 == -1)
    printf("fd2 is broken: %s\n", strerror(errno));

  
  char *buffer = (char *)malloc(1024);
  
  int readfile = scanf(fd1, buffer, sizeof(buffer));
  printf("buffer: %s\n", buffer);
*/
