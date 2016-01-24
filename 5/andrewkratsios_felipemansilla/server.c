#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void sighandler(int signo){
  int status;
  int error;
  if (signo==SIGPIPE){
    error=close(socket_client);
    if (error == -1)
	perror("Error closing client socket\n");
    printf("Client disconnected, child exiting\n");
    exit(42);
  }
  if (signo==SIGINT){
    while (wait(NULL) > 0){
      //parent waits until all children have exited
      ;
    }
    if (getppid() != ppid){
      //Exit procedure for children
      printf("Child exiting\n");
      error=close(socket_client);
      if (error == -1)
	perror("Error closing client socket\n");
      exit(42);
    }
    else{
      error=close(socket_id);
      if (error == -1)
	perror("Error closing main socket\n");
      printf("Main socket closed\n");
      error=semctl(semget(ftok(file_path, sem_id),0,0),0,IPC_RMID,0);
      if (error==-1)
	printf("Error removing semaphores: %s\n",strerror(errno));
      printf("Semaphores removed\n");
      exit(42);
    }
  }
}

//idk if this helps

void setup(){
  int error=mkdir("root", 0777);
  if (error == -1)
    perror("Root directory already exists\n");
  printf("Root directory established\n");
  int fd = open("root/log.txt", O_RDWR | O_APPEND | O_CREAT,0664);
  if (fd < 0) {
    perror("Error creating log file\n");
    exit(-1);
  }
  error = close(fd);
  if (error == -1){
    perror("Error closing log file\n");
    exit(42);
  }
  printf("log file established \n");
  fd = open("root/users.txt", O_RDWR | O_APPEND | O_CREAT, 0664);
  if (fd < 0) {
    perror("Error creating user file\n");
    exit(-1);
  }
  error = close(fd);
  if (error == -1){
    perror("Error closing user file\n");
    exit(42);
  }
  printf("userlist established\n");
  int semaphore=semget(ftok(file_path, sem_id),2,0664 | IPC_CREAT | IPC_EXCL);
  if (semaphore==-1){
    printf("Error creating log & userlist semaphore: %s\n",strerror(errno));
    exit(42);
  }
  union semun command;
  unsigned short forks[2]={100,100};
  command.array=forks;
  error=semctl(semaphore,0,SETALL,command);
  if (error==-1){
    printf("Error setting semaphore value: %s\n",strerror(errno));
    exit(42);
  }
}

int main() {

  int socket_id, socket_client;
  int exit_status = 0;
  char input[1024];
  
  //create the socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );
  
  //bind to port/address
  struct sockaddr_in listener;
  listener.sin_family = AF_INET;  //socket type IPv4
  listener.sin_port = htons(6001); //port #
  listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
  bind(socket_id, (struct sockaddr *)&listener, sizeof(listener));
  
  listen( socket_id, 1 );
  printf("<server> listening\n");

  socket_client = accept( socket_id, NULL, NULL );
  printf("<server> connected: %d\n", socket_client );

  //fgets something
  printf("enter a message for the client: ");
  fgets(input, sizeof(input), stdin);
  write( socket_client, input, sizeof(input));
  exit_status ++;
  
  exit_status = 0;

  return 0;
}
