//include header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int suit_able(int *from_suitor) {//file descriptor of suitor(read)
  int to_client ;
  char buffer[100];

  sprintf(buffer, "%d\n", getpid()); //takes getpid into buffer
  mkfifo(buffer, 0644);

  to_server = open("mario", O_WRONLY);
  write(to_server, buffer, sizeof(buffer));

  *from_server = open(buffer, O_RDONLY); // when this returns a value, we know the server has connected to the pipe
  remove(buffer); //removes named pipe so connection can't get high-jacked
  read(*from_server, buffer, sizeof(buffer));
  printf("<client> connection established: [%s]\n", buffer);

  return to_server;
}


int main() {
  int to_server, from_server;
  char buffer[100];
  
  to_server = client_handshake(&from_server);
  while (1) {
    printf("<client> enterstuff:");
    fgets(buffer, sizeof(buffer), stdin);
    write(to_server, buffer, sizeof(buffer));
    read(from_server, buffer,sizeof(buffer) );
    printf("<client> received: [%s]\n", buffer);

}
close (to_server);
close(from_server);

}
