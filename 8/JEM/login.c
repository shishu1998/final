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
  char *yes_no;
  char* one = (char *)malloc(sizeof(char *));
  char *two = (char *)malloc(sizeof(char *));
  newline = (char *)malloc(sizeof(char *));
  usrname = (char *)calloc(50, sizeof(char*));
  yes_no = (char *)malloc(sizeof(char *));
  newline = "\n";
  one ="1"; two = "2";

  printf("=======WELCOME TO MARY'S PROM DATE SERVER=======\nYou want to take Mary out to PROM because she is an awesome person and if you don't want to then you have bad taste in women.\n\nPlease type in 1 if you have an account or 2 if you'd like to make one.\n");
  fgets(yes_no, 5, stdin);
  printf("yes_no value:%s", yes_no);

  if (strcmp(yes_no, one) == 0) {
    printf("Please type in your username:\n");
    fgets(usrname, 1024, stdin);
    printf("username without new line: %s\n", usrname);
  }
  else if (strcmp(yes_no, two) == 0){
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
    printf("buffer: %s\n", buffer);
    
    fclose(fd1);
    return 0;
  }
  else
    printf("STOP SABOTAGING THIS PROGRAM AND GIVE US EITHER 1 OR 2 AS YOUR ANSWER. SMH PEOPLE THESE DAYS");
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
