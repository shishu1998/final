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
  char usrname[5];
  //char *newline;
  char *yes_no;
  char *one = (char *)malloc(3*sizeof(char *));
  char *two = (char *)malloc(3*sizeof(char *));
  //newline = (char *)malloc(sizeof(char *));
  //usrname = malloc(50*sizeof(char));
  //printf("sizeof(usrname) = %d\n", (int)sizeof(usrname));
  
  yes_no = (char *)malloc(sizeof(char *));
  //newline = "\n";
  one ="1\0"; two = "2\0";

  printf("=======WELCOME TO MARY'S PROM DATE SERVER=======\nYou want to take Mary out to PROM because she is an awesome person and if you don't want to then you have bad taste in women.\n\nPlease type in 1 if you have an account or 2 if you'd like to make one.\n");
  fgets(yes_no, 3, stdin);
  
  printf("yes_no value:%s\n", yes_no);
  

  if (strncmp(yes_no, one, 1) == 0) {
    FILE* fd1 = fopen("username.txt", "r");
    printf("Please type in your username:\n");
    fgets(usrname, sizeof(usrname), stdin);
    printf("username without new line: %s\n", usrname);
    char *buffer = (char *)malloc(100*sizeof(char));
    //printf("sizeof(buffer) = %lu\n", sizeof(buffer));
    fread(buffer, sizeof(char), 100, fd1);
    printf("buffer: %s\n", buffer);
    buffer = "";
    printf("buffer after fread/fwrite: %s\n", buffer);    
  }
  else if (strncmp(yes_no, two, 1) == 0){
    FILE* fd1 = fopen("username.txt", "a+");
    printf("Please create a username:\n");
    fgets(usrname, sizeof(usrname), stdin);
    printf("username without new line: %s\n", usrname);
    //strcat(usrname, newline);
    //printf("username WITH new line: %sword\n", usrname);
    //printf("sizeof(usrname) = %lu\n", sizeof(usrname));
    fwrite(usrname, sizeof(char), sizeof(usrname), fd1);
        
    fclose(fd1);
    return 0;
  }
  else
    printf("STOP SABOTAGING THIS PROGRAM AND GIVE US EITHER 1 OR 2 AS YOUR ANSWER. SMH PEOPLE THESE DAYS\n");
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
