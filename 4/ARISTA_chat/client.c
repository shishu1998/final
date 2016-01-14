#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <string.h>
int client_handshake(int *from_server){

  int to_server;
  char buffer[100];

  sprintf(buffer, "%d", getpid());
  mkfifo(buffer, 0644);

  to_server = open("bacon", O_WRONLY);
  write(to_server, buffer, sizeof(buffer));

  *from_server = open(buffer, O_RDONLY);

  read(*from_server, buffer, sizeof(buffer));
  printf("<client> connection established: [%s]\n", buffer);

  return to_server;

}

int main(){

  int to_server, from_server;
  char buffer[100];

  to_server = client_handshake(&from_server);

  while(1){

    printf("<client> enter text: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    printf("<client> input sent to server: [%s]\n",buffer);
    
    if(strncmp(buffer, "exit", sizeof(buffer)) == 0) {
      close(to_server);
      close(from_server);
      exit(0);
    }
    
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer, sizeof(buffer));
    printf("<client> received: [%s]\n", buffer);
		
  }

  close(to_server);
  close(from_server);

  return 0;

}
