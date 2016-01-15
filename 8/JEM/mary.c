//include header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fnctl.h>
#include <sys/types.h>

int hand_in_maryiage(int *from_suitor) {//file descriptor of client (read)
  int mary_server;//file descriptor of server end (write)
  char buffer[100];

  mkfifo("CHAT", 0644);//1
  *from_suitor = open("CHAT", O_RDONLY);//2
  
  remove("CHAT");
  
  read(*from_suitor, line, sizeof(buffer));
  
  mary_server = open(buffer, O_WRONLY);
  
  strnpy(buffer, "Let me take you to PROM!");
  write(mary_server, vuffer, sizeof(buffer));
  return mary_server;
}

    int main() {

    int mary_server, from_suitor;
    char buffer[100];

    mary_server = hand_in_maryiage(&from_suitor);//returns file descriptor of pipe?
    while(1) {
      read(from_suitor, buffer, sizeof(buffer));
      printf("<Mary> received [%s]\n", buffer);
      strncat(buffer, "purple", sizeof(buffer) - 1);
      write (mary_server, buffer, sizeof(buffer));
    }
    close(mary_server);
    close(from_suitor);
    return 0;
  }
}
