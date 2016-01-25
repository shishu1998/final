//runme.c source code

//headers
#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<signals.h>
#include<time.h>

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#include"child.h"  //or src/child.h
#include"parent.h" //or src/parent.h

//globals
const char* filenam = "dontreadme.txt";

//signal handlers
static int sighandler(int signo);

int main(void) {

  //vars
  int fd;
  struct stat statbuf;
  char* msgbuf;
  
  //open file
  if( fd=open(filenam, RD_ONLY) < 0 ) {
    perror("Error opening file:");
    fprintf(stderr, "\n");
    printf("Error, exiting program.\n");
  }

  //alloc msgbuf (struct stat).st_size
  fstat(fd, &statbuf);
  if( msgbuf=(char*)malloc(statbuf.st_size)==NULL ) {
    perror("Error allocating memory:");
    fprintf(stderr, "\n");
    printf("Error, exiting program.\n");
  }

  //read file
  read(fd, 

  printf("Starting runme!\n");  

}

