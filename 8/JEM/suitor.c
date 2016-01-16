//include header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int suit_able(int *from_suitor) {//file descriptor of suitor(read)
  int to_mary;//file descriptor to open connection/pipe
  char buffer[100];
  sprintf(buffer, "%d\n", getpid()); //takes getpid into buffer
  mkfifo(buffer, 0644);
  to_mary = open("CHAT", O_WRONLY);
  write(to_mary, buffer, sizeof(buffer));

  printf("waiting for connection...\n");

  *from_suitor = open(buffer, O_RDONLY); // when this returns a value, we know the server has connected to the pipe
  remove(buffer); //removes named pipe so connection can't get high-jacked
  read(*from_suitor, buffer, sizeof(buffer));
  printf("<suitor> connection established: [%s]\n", buffer);

  return to_mary;
}


int main() {
  int to_server, from_server;
  char buffer[100];
  
  to_server = suit_able(&from_server);

  while (1) {
    printf("<suitor> enter message:");
    fgets(buffer, sizeof(buffer), stdin);
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer,sizeof(buffer) );
    printf("<suitor> Mary sent a message: [%s]\n", buffer);
  }

  close (to_server);
  close(from_server); 
}
