#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <signal.h>

#include <string.h>

int server_handshake(int *from_client){

  int to_client;
  char line[100];

  mkfifo("bacon", 0644);
  *from_client = open("bacon", O_RDONLY);
  read(*from_client, line, sizeof(line));
  printf("<server> got connection request: [%s]\n", line);
  remove("bacon");

  to_client = open(line, O_WRONLY);
  strncpy(line, "sizzle sizzle", sizeof(line));
  write(to_client, line, sizeof(line));

  return to_client;

}

char process(char *s){
  while(*s) {
	*s = (*s - 'a' + 13) % 26 +'a';
	s++;
  }
}

void client_connection(int to_client, int from_client) {
  
  char line[100];

  while(read(from_client, line, sizeof(line))) {
    printf("<server> received [%s]\n", line);
    process(line);
    printf("<server> processed input\n");
    write(to_client, line, sizeof(line));
    strncpy(line, "", sizeof(line)); 
  }
  
}

void sighandler(int signo) {
	if (signo == SIGINT) {
		remove("bacon");
		printf("Exiting and closing\n");
		exit(0);
	}
}

int main(){

  signal(SIGINT,sighandler);

  int to_client, from_client;;

  while(1){
    printf("<server> waiting for connection\n");
    to_client = server_handshake(&from_client);

    client_connection(to_client, from_client);

    if(!(fork())) {
	client_connection(to_client, from_client);
        close(to_client);
    }

  }

  return 0;
}
