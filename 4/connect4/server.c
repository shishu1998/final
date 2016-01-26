#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "client_relations.h"

static void sighandler( int signo ) {
  if (signo == SIGINT) {
    remove("aaron"); //remove the pipe

    //destroy shared memory and semaphore
    int shared_mem_key;
    if ((shared_mem_key = ftok("Makefile", 0)) == -1) printf("%s\n",strerror(errno));
    //create a var for the shared memory id
    int shared_mem_id;
    
    //create a key for the semaphore
    int sem_key;
    if ((sem_key = ftok("Makefile",1)) == -1) printf("%s\n",strerror(errno));;
    //create a var for the semaphore id
    int sem_id;
    if ((shared_mem_id = shmget(shared_mem_key, sizeof(int), 0644 | IPC_CREAT)) == -1) printf("%s\n",strerror(errno));
    if ((shmctl(shared_mem_id, IPC_RMID, NULL)) == -1) printf("%s\n",strerror(errno));
    sem_id = semget(sem_key, 1, 0644);
    if (sem_id <0) printf("%s\n", strerror(errno));
    if ((semctl(sem_id, 0, IPC_RMID)) == -1) printf("%s\n", strerror(errno));
    
    exit(0);
  }
}


int server_handshake( int *from_client ) {

  int to_client;
  char buffer[256];
  int parent;
  printf("Looking for new connection\n");
  while (1) {
    mkfifo( "aaron", 0644 );
    *from_client = open( "aaron", O_RDONLY );

    remove( "aaron" );

    read( *from_client, buffer, sizeof(buffer) );

    parent = fork();
    if (!parent) {
      printf( "<server> connection established: [%s]\n", buffer );
      to_client = open( buffer, O_WRONLY ); //connect downstream
      strncpy( buffer, "You found aaron. Choose your game or type help.", sizeof(buffer) );
      write( to_client, buffer, sizeof(buffer) ); //send initial message
      printf("Looking for new connection\n");
      return to_client;
    }
  }
}

char * process( char *s ) {
  return  server_understand(s);
}

void client_connection( int to_client, int from_client ) {

  char buffer[256];

  while( read( from_client, buffer, sizeof(buffer) ) ) {
    printf( "<server> received [%s] from client %d\n", buffer, getpid() - 1);
    strncpy( buffer, process(buffer), sizeof(buffer));
    write( to_client, buffer, sizeof(buffer) );
    strncpy( buffer, "", sizeof(buffer) );
  }
}

int main() {

  int to_client;
  int from_client;

  signal(SIGINT,sighandler);

  //set up shared memory and semaphore
  int shared_mem_key;
  if ((shared_mem_key = ftok("Makefile", 0)) == -1) printf("%s\n",strerror(errno));
  int shared_mem_id;
  int sem_key;
  if ((sem_key = ftok("Makefile",1)) == -1) printf("%s\n",strerror(errno));;
  int sem_id;
  if((shared_mem_id = shmget(shared_mem_key, sizeof(int), 0644 | IPC_CREAT)) == -1) strerror(errno);
  int * data = shmat(shared_mem_id, (void *) 0, 0);
  if (data == (int *)(-1)) printf("%s\n", strerror(errno)); //check for error
  *data = 0;
  if ((shmdt(data)) == -1) printf("%s\n",strerror(errno)); //also check for error
  sem_id = semget(sem_key, 1, 0644 | IPC_CREAT);
  if (sem_id < 0) printf("%s\n",strerror(errno));
  union semun su;
  su.val = 2;
  if ((semctl( sem_id, 0, SETVAL, su)) == -1) printf("%s\n",strerror(errno));;
  
  printf("<server> waiting for connection\n");
  to_client = server_handshake( &from_client );

  client_connection( to_client, from_client );

  close( to_client );


  return 0;
}
