#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>


int ships[5] = {0, 0, 0, 0, 0};

union semun {
   int val;
   struct semid_ds *buf;
   unsigned short *array;
   struct seminfo *_buf;
};

int server_handshake(int *from_client){

  int to_client;
  char buff[100];

  mkfifo( "popeye", 0644 );
  *from_client = open( "popeye", O_RDONLY );

  remove("popeye");
  
  read(*from_client, buff, sizeof(buff));
  printf("Sea-Faring Opponent %s, has been spotted!\n", buff);
  to_client = open( buff, O_WRONLY );
  
  strncpy( buff, "Prepare for War!", sizeof(buff) );
  write(to_client, buff, sizeof(buff));
   
  return to_client;
}

static void sighandler(int signo){
  if (signo == SIGINT){
    printf("\nClosing Shop\n");
    remove("popeye");
    exit(0);
  }
}


/*======== int makeFleet() ==========
Inputs: 
int place: user's inputted placement of a ship
int places[]: array holding all ship places

Result:
fills up places[] with user's inputs (sets coordinates of ships)

====================*/
int makeFleet(){
  int pos;
  int i;
  for(i = 0; i<ships.length;i++){
    printf("Input a ship location on the grid (Note input as two-digit e.g 11 instead of 1,1):");
    scanf("%d", &pos);
    if (dontBreak(pos) == 1)
      ships[i] = pos;
    else{
      while (dontBreak(pos) != 1){
	printf("Please enter a valid location: ");
	scanf("%d", &pos);
      }
      ships[i] = pos;
    }
  }
  
}

/*======== int dontBreak()  ==========

check to see is 11-15, 21-25, 31-35, 41-45, 51-55
also cehck to see no double entries
Inputs: 


Result:
makes it harder for someone to break our program
if okay = 0, then there's a problem.

====================*/
int dontBreak(int pos){
  int okay = 0;
  //check to see within range
  
  if ( ((pos > 10)&&(pos < 16)) ||
       ((pos > 20)&&(pos < 26)) ||
       ((pos > 30)&&(pos < 36)) ||
       ((pos > 40)&&(pos < 46)) ||
       ((pos > 50)&&(pos < 56)) ){
    okay = 1;
  }

  //check to see no double entries
  okay = isInShips(pos)
  
  return okay;
}

int isInShips(int pos){
  int okay = 1;
  if (pos == ships[0] ||
      pos == ships[1] ||
      pos == ships[2] ||
      pos == ships[3] ||
      pos == ships[4]){
    okay = 0;
  }
  return okay;
}

int isHit(int pos){
  int hit =  isInShips(pos);

  if (hit){
    int i;
    for (i = 0; i < ships.length; i++)
      if (ships[i] == pos)
	ships[i] = 0;
  }

  return hit;
}

int isAllHit(){
  int allhit = 0;

  if (0 == ships[0] &&
      0 == ships[1] &&
      0 == ships[2] &&
      0 == ships[3] &&
      0 == ships[4]){
    allhit = 1;
  }

  return allhit;
}

//THIS GONNA HAVE TO BE MOVED TO MAIN
void server_game_control(int to_client, int from_client, int *currentcoordinate) {
  int coord;
  char result[100];
    
  while( read(from_client, result, sizeof(result) )){
    //Reads from Opponent Whether or Not Your Hit was successful
    printf("You Got Back from Opponent: %s\n", result);
    //Attempts to Down Semaphore to Access Shared Memory
    //Once Semaphore is Downed, Reads Shared Memory to See What Coordinate Opponnet Wrote 
    coord = *currentcordinate;
    if (isHit(coord)){
      if (isAllHit()){
	strncpy(result,"All Ships Eliminated!",sizeof(result));
	write(to_client, result, sizeof(result) );
      }
      else{
	strncpy(result,"Ship Hit!",sizeof(result));
	write(to_client, result, sizeof(result) );
      }
    }
    else{
      strncpy(result,"Ship Missed!",sizeof(result));
      write(to_client, result, sizeof(result) );
    }
    strncpy(result,"",sizeof(result));
    //Player 1 Gives Program a Ship Location
    printf("Input a ship location on to hit your opponent's grid (Note input as two-digit e.g 11 instead of 1,1):");
    scanf("%d", &pos);
    //Ship Location is Put Into Shared Memory
    //Semaphore is Upped
  }
}



int main(){
  signal( SIGINT, sighandler );
  //creating & initializing shared memory and semaphore
  //create & initialize shared mem
  int shmid = shmget(ftok("makefile",13),sizeof(int), 0664| IPC_CREAT | IPC_EXCL);
  printf("Trying to create the shared memory...\n");
  if(shmid == -1){
    printf("There was a problem in creating the shared memory\n");
    printf("Error %d: %s\n", errno, strerror(errno));
  } else{
    printf("Success!\n");
  }
  int *currentcoordinate = (int *) shmat(shmid, 0, 0);
  printf("Trying to attach the shared memory to a variable...\n");
  if(*currentcoordinate == -1){
    printf("There was a problem in attaching the shared memory to a variable\n");
    printf("Error: %d: %s\n", errno, strerror(errno));
    return;
  } else{
    printf("Success!\n");
  }
  *currentcoordinate = 0;

  //creating & initialize  semaphore
  int semid;
  int ret;
  struct sembuf new = {0, -1, SEM_UNDO};
  semid = semget(ftok("makefile",47), 1, 0644 | IPC_CREAT);
  printf("Trying to create the semaphore...\n");
  if (semid == -1){
    printf("There was a problem in creating the semaphore\n");
    printf("Error %d: %s\n", errno, strerror(errno));
  } else{
    printf("Success!\n");
  }
  union semun data;
  data.val = 1;
  printf("Trying to set the semaphore...\n");
  ret = semctl(semid,0,SETALL,&data);
  if (ret == -1){
    printf("There was a problem in setting the semaphore\n");
    printf("Error %d: %s\n", errno, strerror(errno));
  } else{
    printf("Success!\n");
  }
  
  //initialize game parameters
  makeFleet();
  
  int to_client;
  int from_client;
  while(1){
    printf("Trying to down the semaphore...\n");
    ret = semop(semid, &new, 1);

    printf("Wating for your Sea-Faring Opponent to Connect\n");
    to_client  = server_handshake(&from_client);
    
    int coord;
    char result[100];
    //Player 1 Takes the First Turn
    
    //All Turns After First
    while( read(from_client, result, sizeof(result) )){
      //Reads from Opponent Whether or Not Your Hit was successful                                                                                                                  
      printf("You Got Back from Opponent: %s\n", result);
      //Attempts to Down Semaphore to Access Shared Memory
      printf("Trying to down the semaphore...\n");
      ret = semop(semid, &new, 1);
      if(ret == -1){
	printf("There was a problem in downing the semaphore\n");
	printf("Error: %d: %s\n", errno, strerror(errno));
	return;
      }
      else
	printf("Success!\n");
      //Once Semaphore is Downed, Reads Shared Memory to See What Coordinate Opponnet Wrote                                                                                    
      coord = *currentcordinate;
      if (isHit(coord)){
	if (isAllHit()){
	  strncpy(result,"All Ships Eliminated!",sizeof(result));
	  write(to_client, result, sizeof(result) );
	  break;
	}
	else{
	  strncpy(result,"Ship Hit!",sizeof(result));
	  write(to_client, result, sizeof(result) );
	}
      }
      else{
	strncpy(result,"Ship Missed!",sizeof(result));
	write(to_client, result, sizeof(result) );
      }
      strncpy(result,"",sizeof(result));
      //Player 1 Gives Program a Ship Location                                                                                                      
      printf("Input a ship location on to hit your opponent's grid (Note input as two-digit e.g 11 instead of 1,1):");
      scanf("%d", &pos);
      //Ship Location is Put Into Shared Memory
      *currentcoordinate = pos;
      //Semaphore is Upped
      new.sem_op = 1;
      semid = semget(ftok("makefile", 47), 1, 0644);
      printf("Trying to up the semaphore...\n");
      ret = semop(semid, &new, 1);
      if(ret == -1){
	printf("There was a problem in upping the semaphore\n");
	printf("Error %d: %s\n", errno, strerror(errno));
      }
      else
	printf("Success!\n");

    }
    printf("The Game has ended!\n")
    close( to_client);
  }

  return 0;
}
    
