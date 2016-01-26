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

//This is just copied from your source code (mostly)
int client_handshake( int *from_server ) {

  int to_server;
  char buffer[100];

  sprintf(buffer, "%d", getpid() );
  mkfifo( buffer, 0644 );

  printf("Awaiting connection \n");
  to_server = open( "aaron", O_WRONLY );
  write( to_server, buffer, sizeof(buffer) );

  *from_server = open( buffer, O_RDONLY );
  remove( buffer );

  read( *from_server, buffer, sizeof(buffer) );
  printf("Connection Established: [%s]\n", buffer );

  return to_server;
}


int main() {

  int to_server;
  int from_server;
  char buffer[256];
  printf("If you wish to exit, you must connect first\n");
  int sem_key;
  if ((sem_key = ftok("Makefile",1)) == -1) printf("%s\n",strerror(errno));
  int sem_id = semget(sem_key, 1, 0644);
  if (sem_id < 0) printf("%s\n",strerror(errno));

  //set up the sempahore operation
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1; 
  if ((semop( sem_id, &sb, 1)) == -1) printf("%s\n",strerror(errno));
  
  to_server = client_handshake( &from_server );

  int shared_mem_key;
  if ((shared_mem_key = ftok("Makefile", 0)) == -1) printf("%s\n",strerror(errno));
  int shared_mem_id;
  if((shared_mem_id = shmget(shared_mem_key, sizeof(int), 0644)) == -1) printf("%s\n",strerror(errno));

  int * data = shmat(shared_mem_id, (void *) 0, 0);
  if (data == (int *)(-1)) printf("%s\n",strerror(errno));

  int div = * data;
  *data = (*data + 1) % 2;
 
  
  initiate_text();
  printf("Hold on!\n");
  
  while (1) {
    sleep(1);
    while ((num_of_turns() % 2) != div) {
      sleep(1);
    }
    print_board();
    printf("It is your turn.\n");
    fgets( buffer, sizeof(buffer), stdin );
    *strchr( buffer, '\n') = 0;
    client_understand(buffer);
    if (strcmp(buffer,"exit") == 0) exit(0);
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer, sizeof(buffer));
    printf("%s\n", buffer );
    strncpy( buffer, "", sizeof(buffer) );
  }

  close( to_server );
  close( from_server );

  return 0;
}
