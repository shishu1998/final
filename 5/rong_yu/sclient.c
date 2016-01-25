#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


int main(){

  struct sembuf checker;

  checker.sem_num = 0;//first one
  checker.sem_flg = SEM_UNDO;
  checker.sem_op = -1;

  printf("Now Attempting to Access the Story:\n");
  int semid = semget( ftok("key", 1), 1, 0644);
  if (semid < 0){
    printf("Error: %s", strerror(errno));
    return;
  }
  semop(semid, &checker, 1);
  printf("You're now in!\n");

  int sd = shmget( ftok("key", 2), sizeof(int), 0644);
  if (sd < 0){
    printf("Error: %s", strerror(errno));
    return;
  }
  int *num = shmat( sd, 0,0);

  int fd = open("stuff", O_RDWR);

  char buffer[256];
  lseek( fd, (-1 * *num), SEEK_END);
  read(fd, buffer, *num);
  buffer[*num] = NULL;

  printf("The last line was: %s\n", buffer);
  printf("What do you want to add?\n\n");

  fgets(buffer, sizeof(buffer), stdin);

  //int *size; //has to be num, as original
  *num = strlen(buffer);
  buffer[*num-1] = "\n"; //can't be null, or else it'll cut it off later

  //printf("This work\n");
  lseek(fd, 0, SEEK_END);
  write(fd, buffer, *num);
  close(fd);

  //printf("this work");
  
  checker.sem_op = 1;
  semop(semid, &checker, 1);
  
  int e = shmdt(num); //if not *int, shmdt won't work
  if (e<0){
    printf("Problem: %s\n", strerror(errno));
  }

  printf("It has been added\n");
}
