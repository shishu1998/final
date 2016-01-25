
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <errno.h>
#include "semun.h"


int main(int argc, char *argv[]){
  
  int key = ftok("key", 1);
  int semid;
  if ( (strcmp(argv[1], "-c") == 0) ) {
    
    printf("Creating semaphore \n");
    semid = semget( key, 1, 0644 | IPC_CREAT );
    union semun su;
    su.val = 1;
    semctl( semid, 0, SETVAL, su);

    
    printf("Creating shared memory \n");
    int sd = shmget( ftok("key", 2), sizeof(int), 0644 | IPC_CREAT );
    if (sd < -1){
      printf("Error: %s\n", strerror(errno));
    }
    //int segmentID = ( int *) shmat(sd, 0, 0);
    //printf("Int: %d\n", &segmentID);
    //segmentID = 0;

    
    printf("Creating the file\n");
    int fd = open("stuff", O_WRONLY | O_TRUNC | 0644);
    if (fd < 0){
      printf("Error: %s\n",strerror(errno));
      return;
    }
    close(fd);
    
  } 
  if ( (strcmp(argv[1], "-r") == 0) ) {
    int fd = open("stuff", O_RDONLY);
    char words[2048];
    int last = read(fd, words, sizeof(words));
    printf("The number of words read is: %d\n", last);
    words[last] = NULL;
    printf("The story: \n %s", words);
    close(fd);
    int fd2 = open("stuff", O_WRONLY | O_TRUNC);
    close (fd2);

    semid = semget( key, 1, 0644 );
    semctl( semid, 0, IPC_RMID );
    int mem = shmget( ftok("key", 2), 1, 0644);
    shmctl(mem, IPC_RMID, 0);
    
  }
}
